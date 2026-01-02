  ## Project Goals

### Goal 1: Self-contained Simple Compiler (✅ ≈99.78% completed)
**ENG:** This compiler can ***directly*** *(without invoking or depending on any external compiler during the compilation process)* generate machine code for WIntel32 (x86 + Win32).<br>
To compile the compiler itself, you can use:

**UKR:** Цей компілятор може ***напряму*** *(не викликає і не залежить від жодного зовнішнього компілятора під час процесу компіляції)* генерувати машинний код для WIntel32 (x86 + Win32).<br>
Для компіляції самого компілятора можна використати:

https://github.com/KozakNazar1/compiler_compiler_2025

### Goal 2: Model Theory Research Platform (🔄 ≈23% completed)
**ENG:** This compiler serves as a research tool for exploring computation models and interpretations between them. It investigates both practical aspects — mapping software representations of simple automata (for formal languages of various levels) to hardware structures (RTL/ESL/TLM descriptions) — and fundamental theoretical questions of mathematical logic, primarily in model theory.

**UKR:** Цей компілятор є інструментом для наукових досліджень у галузі моделей обчислень та інтерпретацій між ними. Досліджуються як практичні аспекти відображення програмних реалізацій простих автоматів (для формальних мов різного рівня) у апаратні структури (RTL/ESL/TLM-описи), так і фундаментальні теоретичні питання математичної логіки — насамперед теорії моделей.

### Goal 3: Compiler with self-contained self-compiling (🚧 beginning stage)
**ENG:** Another goal of this project is to create a compiler that does not require any other compiler to compile itself ***(does not even need its own compiled version for recompilation)***.

**UKR:** Ще однією метою цього проекту є створення компілятора, який не потребує жодного іншого компілятора для компіляції себе самого ***(не потребує навіть власної скомпільованої версії для перекомпіляції)***.

### Goal 4: Self-configurable Compiler-on-Chip (🚧 beginning stage)
*(self-configurable Hardware Implementation of Compiler)*  

**ENG:** Research on implementing the compiler as a hardware IP‑core (ASIC/FPGA) that enables direct source‑to‑binary transformation without conventional software toolchains. The static compilation logic is synthesized, while the reconfigurable part is generated either as memory tables (without synthesis) or as synthesized direct logic.

**UKR:** Дослідження реалізації компілятора у вигляді апаратного IP-ядра (ASIC/FPGA), яке забезпечує пряме перетворення вихідного коду у бінарний формат без використання стандартних програмних інструментів. Статична логіка компіляції синтезується, тоді як реконфігурована частина генерується або як таблиці для пам'яті (без синтезу), або як безпосередньо синтезована логіка.
