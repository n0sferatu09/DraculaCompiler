# The Dracula Compiler

**Dracula** is compiler for C, that is also written in The C Programming Language. 
This is learning project designed to learn The C Programming Language and Compiler Theory.

> 🧛 For now, it’s more frightening in its name than in its possibilities, 
but work on it is in full swing!

## Project Status 

The compiler is in an early stage of active development. Current Focus:

- [ ] **In Process:** Writting a Lexer.
- [ ] Writting a Parser.
- [ ] Building a AST.
- [ ] Writting a Semantic Analyzer.
- [ ] Writting a Code Generator.

The compiler is not ready for use yet. Stay tuned for updates!

**To install, enter the following into the terminal:**

```bash
git clone https://github.com/n0sferatu09/DraculaCompiler.git

```

## How to use?

1. Open the **main.c** file.

2. In the main function, find the line of code:

```C
    file = fopen("filename.c", "r");
```

3. Replace **"filename.c"** with your file.

4. Enter in the terminal:

```Shell
    ./build.sh
```

5. Open the **main.c** file.

## Licence
### **MIT Licence**
Copyright (c) 2025 [Nokito Nosferatu]
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
