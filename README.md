# Elevatorlab
Elevator


## Clang formatter
To ensure that code formatting is consistent across all code written - regardless of who writes it, use the following command in the source folder:

```
clang-format -i -style=llvm *.cpp *.h
```

(This uses llvm which is a fairly common C/C++ style)