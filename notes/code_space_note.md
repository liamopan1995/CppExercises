# notes
### **Start from raw g++ commands**    
    build objects:

    g++ -g -Wall -c main.cpp -o main.o
    ...
    create final excutable by linking objects
    g++ -g -Wall main.o my_utils.o -o my_program

It is hard to do things this way as the objects and files are getting large in number.

Great question! The reason **"Link object files to create the final executable"** appears **before** **"Compile source files into object files"** in the Makefile is **not about execution order but about rule declaration**.

### **How Makefile Works**
A Makefile **does not execute rules in the order they are written**. Instead, `make` follows **dependency relationships** to determine the correct order of execution.

Let's break it down:

---

## **1️⃣ `make` Starts with the First Target (Default Target)**
```makefile
all: $(OBJ_DIRS) $(TARGET)
```
- The first target (`all`) is the default when you run `make`.  
- `all` **depends on**:
  - `$(OBJ_DIRS)`: Ensures required directories exist.
  - `$(TARGET)`: The final executable.

Since `all` depends on `$(TARGET)`, `make` now looks at:

---

## **2️⃣ `$(TARGET)` (Final Executable) Depends on `$(OBJS)`**
```makefile
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)
```
- `$(TARGET)` (which is `make_gen/main`) **depends on** `$(OBJS)` (all `.o` files).
- `make` checks if **all object files exist**.
  - If they **don’t exist** or are **outdated**, it finds a rule to build them.
  - If they **exist and are up-to-date**, it skips compilation and proceeds to linking.

---

## **3️⃣ `$(OBJS)` (Object Files) Depend on `.cpp` Files**
```makefile
$(BUILD_DIR)/%.o: %.cpp | $(OBJ_DIRS)
	$(CXX) $(CXXFLAGS) -c $< -o $@
```
- `make` finds that object files are **produced from `.cpp` files**.
- If `main.o` or `src/my_utils.o` does not exist (or is outdated), `make` compiles them.

---

### **Execution Order (Driven by Dependencies, NOT Code Order)**
1️⃣ **Ensure `$(OBJ_DIRS)` (directories) exist.**  
   - If they do not exist, `mkdir -p` creates them.

2️⃣ **Compile `.cpp` files into `.o` files.**  
   - If `make_gen/main.o` or `make_gen/src/my_utils.o` is missing or outdated, it gets compiled.

3️⃣ **Link `.o` files into `$(TARGET)` (final executable).**  
   - If `$(TARGET)` is missing or outdated, it gets linked.

---

### **Why the Rules are Written in This Order?**
Writing the **linking rule before the compilation rule** is a convention in Makefiles because:
1. **Top-Down Readability**  
   - The most important rule (`all`) and its final goal (`$(TARGET)`) are defined first.
   - Readers see **what the Makefile produces** before diving into how individual files are built.

2. **Make's Dependency Resolution Handles the Correct Order**  
   - Even though the **linking rule appears first**, it **won't execute until all its dependencies (object files) are built**.

---

### **What Happens if You Swap the Order in the Makefile?**
If you put:
```makefile
$(BUILD_DIR)/%.o: %.cpp | $(OBJ_DIRS)
```
before:
```makefile
$(TARGET): $(OBJS)
```
It **would still work exactly the same way** because `make` **follows dependencies**, not the order of rules in the file.

However, it’s harder to read:
- You first see rules for compiling `.cpp` to `.o`, without knowing **why they are needed**.
- The linking step (which is the final goal) appears **later**, making it less intuitive.

---

### **Conclusion**
- The Makefile **executes rules based on dependencies, NOT on the order they are written**.
- The linking rule **comes first** for **readability**, showing the final goal before breaking it down into steps.
- The compilation rule **executes first** because it is a dependency of the linking rule.

**TL;DR**: **Order in the Makefile doesn’t control execution—dependencies do!** 🚀




### 构建并使用一个so

@liamopan1995 ➜ /workspaces/CppExercises (main) $ cd lib/
@liamopan1995 ➜ /workspaces/CppExercises/lib (main) $ g++ -fPIC -I ../include -c my_so.cpp -o my_so.o
@liamopan1995 ➜ /workspaces/CppExercises/lib (main) $ g++ -shared -o libmy_so.so my_so.o 
@liamopan1995 ➜ /workspaces/CppExercises/lib (main) $ cd ..
@liamopan1995 ➜ /workspaces/CppExercises (main) $ g++ -g -Wall -I include  -pthread -o make_gen/main make_gen/main.o make_gen/src/derived.o make_gen/src/my_utils.o -L ./lib/ -lmy_so

在依赖这个so文件后， 原有的makefile 不好用了 我们需要更新它
---

## **共享库(.so)运行时问题**

**问题**："cannot open shared object file: libmy_so.so"
- **编译时**：链接器知道去 `-L ./lib/` 找库 ✓
- **运行时**：系统不知道去哪里找库 ✗

**三个解决方案**：

### **方案1：运行时设置环境变量（临时）**
```bash
LD_LIBRARY_PATH=./lib ./make_gen/main
```

### **方案2：编译时嵌入库路径（推荐）**
```bash
g++ -g -Wall -I include -pthread -o make_gen/main \
    make_gen/main.o make_gen/src/derived.o make_gen/src/my_utils.o \
    -L ./lib/ -lmy_so -Wl,-rpath,./lib
```
- `-Wl,-rpath,./lib`：把库路径写入可执行文件内部
- 运行时动态链接器会按此路径查找库，无需环境变量

### **方案3：在Makefile中永久配置（最佳）**
```makefile
LDFLAGS = -L ./lib/ -Wl,-rpath,./lib
LIBS = -lmy_so

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDFLAGS) $(LIBS)
```