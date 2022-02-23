# COMP7500 Advanced Operating Systems 
## Project 3 Notes



### How to format printing result in C？
```
number = 1;
print("Task%2d Task",number);
```

result:
Task 1

a space in left.
```
print("%-2d",number);
```

result:
1 Task
a space in right.

```
number = 123
print("%-2dTask",number);
```
result:
123Task
No space but it printed all number.

print("%2.2f",number);
