#include <iostream>
#include <fstream>
#include <string>

#include <g2o/types/slam2d/types_slam2d.h>
#include <g2o/core/block_solver.h>
#include <g2o/core/optimization_algorithm_levenberg.h>
#include <g2o/core/optimization_algorithm_gauss_newton.h>
#include <g2o/solvers/dense/linear_solver_dense.h>

using namespace std;
using namespace g2o;

/************************************************
 * This program demonstrates how to use g2o solver
 * for 2D SLAM optimization.
 * It reads a Pose graph from a .g2o file and performs optimization.
 ************************************************/

int main( int argc, char** argv )
{
    if ( argc != 2 )
    {
        cout << "Usage: pose_graph_g2o_SE2 input.g2o" << endl;
        return 1;
    }
    ifstream fin( argv[1] );
    if ( !fin )
    {
        cout << "File " << argv[1] << " does not exist." << endl;
        return 1;
    }

    // Setting up the optimizer
    typedef BlockSolver<BlockSolverTraits<-1, -1>> Block;
    Block::LinearSolverType* linearSolver = new LinearSolverDense<Block::PoseMatrixType>();
    Block* solver_ptr = new Block(std::unique_ptr<Block::LinearSolverType>(linearSolver));
    // choose one of these 2 optimizers
    //OptimizationAlgorithmLevenberg* solver = new OptimizationAlgorithmLevenberg(std::unique_ptr<Block>(solver_ptr));
    OptimizationAlgorithmGaussNewton* solver = new OptimizationAlgorithmGaussNewton(std::unique_ptr<Block>(solver_ptr));
    
    SparseOptimizer optimizer;
    optimizer.setAlgorithm(solver);

    // Reading from the .g2o file
    int vertexCnt = 0, edgeCnt = 0;
    while (!fin.eof())
    {
        string name;
        fin >> name;
        if (name == "VERTEX_SE2")
        {
            VertexSE2* v = new VertexSE2();
            int id;
            fin >> id;
            v->setId(id);
            v->read(fin);
            optimizer.addVertex(v);
            vertexCnt++;
            if (id == 0)
                v->setFixed(true); // Fix the first vertex
        }
        else if (name == "VERTEX_XY")
        {
            VertexPointXY* v = new VertexPointXY();
            int id;
            fin >> id;
            v->setId(id);
            v->read(fin);
            optimizer.addVertex(v);
            vertexCnt++;
        }
        else if (name == "EDGE_SE2")
        {
            EdgeSE2* e = new EdgeSE2();
            int id1, id2;
            fin >> id1 >> id2;
            e->setId(edgeCnt++);
            e->setVertex(0, optimizer.vertices()[id1]);
            e->setVertex(1, optimizer.vertices()[id2]);
            e->read(fin);
            optimizer.addEdge(e);
        }
        else if (name == "EDGE_SE2_XY")
        {
            EdgeSE2PointXY* e = new EdgeSE2PointXY();
            int id1, id2;
            fin >> id1 >> id2;
            e->setId(edgeCnt++);
            e->setVertex(0, optimizer.vertices()[id1]);
            e->setVertex(1, optimizer.vertices()[id2]);
            e->read(fin);
            optimizer.addEdge(e);
        }
        // logic to hadndel the FIX num line in g2o files, which fix the vertex with ID:num 
        else if (name == "FIX")
        {
            int fixedVertexId;
            fin >> fixedVertexId;
            OptimizableGraph::Vertex* v = optimizer.vertex(fixedVertexId);
            if (v)
                v->setFixed(true);
        }
        if (!fin.good())
            break;
    }

    cout << "Read total " << vertexCnt << " vertices, " << edgeCnt << " edges." << endl;

    cout << "Preparing optimization..." << endl;
    optimizer.setVerbose(true);
    optimizer.initializeOptimization();
    cout << "Starting optimization..." << endl;
    optimizer.optimize(30);

    cout << "Saving optimization results..." << endl;
    optimizer.save("result_2d.g2o");

    return 0;
}
