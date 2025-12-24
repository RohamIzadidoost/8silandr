import sys
# --- 1. Fast I/O Setup ---
input = sys.stdin.readline 
# Bulk Read (Reads entire input at once)
data = sys.stdin.read().split()
iterator = iter(data)
# usage: val = next(iterator)

# --- 2. String Manipulation (Strip) ---
s = "  Hello World  \n"
clean = s.strip()   # "Hello World" (Both sides)
left  = s.lstrip() or rstrip()
# --- 3. Iterators ---
names = ["Alice", "Bob"]
ages = [25, 30]
# Enumerate (Index + Value)
for i, name in enumerate(names):
    # i=0, name="Alice"...
# Zip (Two lists at once)
for name, age in zip(names, ages):
    # name="Alice", age=25...
# --- 4. Output Formatting ---
x = 42
pi = 3.14159
print(f"{x:05d}")    # 00042 (Zero pad)
print(f"{x:<5d}")    # "42   " (Left align)
print(f"{pi:.3f}")   # 3.142 (Precision)
print(f"{pi:7.2f}")  # "   3.14" (Width 7, 2 decimals)
