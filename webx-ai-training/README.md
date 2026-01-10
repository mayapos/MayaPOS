# WebX Language — AI Training Dataset (and companion references)

This repository provides **resources to help WebX (Harbour) developers use AI-assisted development effectively and safely**.

It currently contains six core resource groups:

- A **GPT-ready WebX Language rulebook** (living document).
- An example **personal coding standards** document to keep AI-generated WebX (Harbour) code consistent (adapt it to your needs).
- A machine-readable **WebX (Harbour) function definitions** dataset in **YAML**, intended for AI-assisted code generation and documentation.
- A **C ↔ WebX (Harbour) interop guide** (Markdown chapters + a compiled PDF), including an **English translation** (with author approval) of *"The New Buccaneers — Episode 2"* by Manu Expósito Suárez.
- **WebX GUI Classes reference** - Complete documentation for WebX's proprietary GUI classes (TWindow, TLayout, TButton, etc.).
- **Designer → AI workflow guide** - Step-by-step instructions for enhancing visual layouts with AI assistance.

---

## What’s in this repo

### 1) GPT-ready guidance documents

- **AI Quick Start** (30-second primer, syntax cheat sheet, workflow checklist): [`AI_QUICK_START.md`](./AI_QUICK_START.md) ⭐ **START HERE**
- **🚨 Output Format Rules** (critical safety rule: always generate .prg files, not .html/.php): [`OUTPUT_FORMAT_RULES.md`](./OUTPUT_FORMAT_RULES.md) ⭐ **IMPORTANT**
- **WebX Deployment Options** (CGI, FastCGI, Server, PHP, mod_WebX, mod_harbour): [`webx_deployment_options.md`](./webx_deployment_options.md)
- Unified WebX (Harbour) rulebook (codegen guardrails + semantics): [`webx_language_rules.md`](./webx_language_rules.md)
- Example "project defaults" prompts/snippets (how to constrain AI in a specific repo):
  [`Example_webx_language_rules_ProjectDefaults.md`](./Example_webx_language_rules_ProjectDefaults.md)
- Personal cross-project coding standards (formatting, naming, etc.):
  [`personal_coding_standards.md`](./personal_coding_standards.md)
- **WebX GUI Classes reference** (TWindow, TLayout, TButton, TSay, TGet, etc.): [`webx_gui_classes.md`](./webx_gui_classes.md)
- **Designer → AI workflow** (visual layout to functional app): [`webx_designer_workflow.md`](./webx_designer_workflow.md)

### 2) Function dataset (machine-readable YAML)

- YAML schema and conventions: [`SPEC_webx_functions.md`](./SPEC_webx_functions.md)
- Manifest (slug → part file map): [`webx_functions/index.yaml`](./webx_functions/index.yaml)
- Function definitions (current single-part dataset):  
  [`webx_functions/webx_functions_part_001.yaml`](./webx_functions/webx_functions_part_001.yaml)
- Convenience snapshot (zip of the two files above):  
  [`webx_functions/webx_functions_2025_12_25_001.zip`](./webx_functions/webx_functions_2025_12_25_001.zip)

### 3) C ↔ WebX (Harbour) interop guide (book-style)

Folder: [`How_to_Interface_Between_C_and_WebX/`](./How_to_Interface_Between_C_and_WebX/)

- Examples bundle: [`How_to_Interface_Between_C_and_WebX/Examples.zip`](./How_to_Interface_Between_C_and_WebX/Examples.zip)
- Cover / index: [`How_to_Interface_Between_C_and_WebX/WebX_C_00_Cover_and_Index.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_00_Cover_and_Index.md)
- Chapter 01: [`How_to_Interface_Between_C_and_WebX/WebX_C_01_Prologue_and_Purpose.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_01_Prologue_and_Purpose.md)
- Chapter 02: [`How_to_Interface_Between_C_and_WebX/WebX_C_02_Tools_Needed.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_02_Tools_Needed.md)
- Chapter 03: [`How_to_Interface_Between_C_and_WebX/WebX_C_03_A_Bit_of_C.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_03_A_Bit_of_C.md)
- Chapter 04: [`How_to_Interface_Between_C_and_WebX/WebX_C_04_Operators.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_04_Operators.md)
- Chapter 05: [`How_to_Interface_Between_C_and_WebX/WebX_C_05_Control_Structures.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_05_Control_Structures.md)
- Chapter 06: [`How_to_Interface_Between_C_and_WebX/WebX_C_06_Elementary_Data_Types.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_06_Elementary_Data_Types.md)
- Chapter 07: [`How_to_Interface_Between_C_and_WebX/WebX_C_07_Structured_Data_Types.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_07_Structured_Data_Types.md)
- Chapter 08: [`How_to_Interface_Between_C_and_WebX/WebX_C_08_Structures_Unions_Enums.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_08_Structures_Unions_Enums.md)
- Chapter 09: [`How_to_Interface_Between_C_and_WebX/WebX_C_09_Typedef_and_Variables.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_09_Typedef_and_Variables.md)
- Chapter 10: [`How_to_Interface_Between_C_and_WebX/WebX_C_10_Pointers.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_10_Pointers.md)
- Chapter 11: [`How_to_Interface_Between_C_and_WebX/WebX_C_11_Dynamic_Memory.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_11_Dynamic_Memory.md)
- Chapter 12: [`How_to_Interface_Between_C_and_WebX/WebX_C_12_VM_Stack_and_Symbol_Table.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_12_VM_Stack_and_Symbol_Table.md)
- Chapter 13: [`How_to_Interface_Between_C_and_WebX/WebX_C_13_C_Functions_for_WebX_Harbour.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_13_C_Functions_for_WebX_Harbour.md)
- Chapter 14: [`How_to_Interface_Between_C_and_WebX/WebX_C_14_Compiling_C_in_PRG.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_14_Compiling_C_in_PRG.md)
- Chapter 15: [`How_to_Interface_Between_C_and_WebX/WebX_C_15_Extended_System.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_15_Extended_System.md)
- Chapter 16: [`How_to_Interface_Between_C_and_WebX/WebX_C_16_Item_API.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_16_Item_API.md)
- Chapter 17: [`How_to_Interface_Between_C_and_WebX/WebX_C_17_Execute_Functions_Methods_CodeBlocks_from_C.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_17_Execute_Functions_Methods_CodeBlocks_from_C.md)
- Chapter 18: [`How_to_Interface_Between_C_and_WebX/WebX_C_18_Error_API.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_18_Error_API.md)
- Chapter 19: [`How_to_Interface_Between_C_and_WebX/WebX_C_19_FileSys_API_.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_19_FileSys_API_.md)
- Chapter 20: [`How_to_Interface_Between_C_and_WebX/WebX_C_20_Creating_Libraries.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_20_Creating_Libraries.md)
- Chapter 21: [`How_to_Interface_Between_C_and_WebX/WebX_C_21_DLL_Interfaces.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_21_DLL_Interfaces.md)
- Chapter 22: [`How_to_Interface_Between_C_and_WebX/WebX_C_22_Garbage_Collector_Internals.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_22_Garbage_Collector_Internals.md)
- Chapter 23: [`How_to_Interface_Between_C_and_WebX/WebX_C_23_Compiler_Optimizations_and_Pcode.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_23_Compiler_Optimizations_and_Pcode.md)
- Chapter 24: [`How_to_Interface_Between_C_and_WebX/WebX_C_24_Multi_Threading_and_TLS.md`](./How_to_Interface_Between_C_and_WebX/WebX_C_24_Multi_Threading_and_TLS.md)
- Compiled PDF: [`How_to_Interface_Between_C_and_WebX/WebX_C_2025_11_10.pdf`](./How_to_Interface_Between_C_and_WebX/WebX_C_2025_11_10.pdf)
- Diagram image: [`How_to_Interface_Between_C_and_WebX/stack_diagram.png`](./How_to_Interface_Between_C_and_WebX/stack_diagram.png)

### 4) Repo meta

- License: [`LICENSE`](./LICENSE) (CC BY-NC-SA 4.0)
- Credits and attributions: [`CREDITS.md`](./CREDITS.md)

---

## How to use these resources with AI

### Traditional Development Workflow:

1. Provide the rulebook (`webx_language_rules.md`) and your project defaults as context (system prompt / project instructions).
2. Provide the function dataset (YAML) as an authoritative "allow-list" for which functions can be used.
3. Use `personal_coding_standards.md` to enforce consistency (formatting, naming, patterns).
4. Use the interop guide when generating `#pragma BEGINDUMP` code or writing C extensions.

### Designer-Driven AI Development Workflow (NEW):

1. **Design visually:** Use `tools/designer_tlayout.html` to create your layout structure
2. **Generate skeleton:** Designer outputs .prg file with TLayout sections and smart TODOs
3. **AI enhancement:** Provide AI with:
   - Generated .prg file
   - `webx_gui_classes.md` (class reference)
   - `webx_designer_workflow.md` (workflow guide)
   - `webx_language_rules.md` (syntax rules)
   - Your functional requirements
4. **AI fills TODOs:** AI preserves layout structure, adds controls and business logic
5. **Compile and run:** Build with WebX compiler, deploy as CGI or mod_harbour

**Benefits:**
- Visual design separated from functional code
- AI understands layout structure and constraints
- Consistent section-based architecture
- Faster development (design → generate → enhance → deploy)

If you are publishing derivative work that includes the translated book content, consider adding an explicit attribution note in your downstream project and verifying that your usage matches the license terms and the author approval conditions described in this repository.

---

## Contributing

The schema and companion documents may evolve. Please open an issue with suggestions or corrections. Pull requests are welcome.

---

## Credits

**Original Dataset Creator:** Eric Lendvai
**WebX Framework & Extensions:** Byron Henderson (MayaPOS)
**C Interop Guide:** Based on "The New Buccaneers — Episode 2" by Manu Expósito Suárez (English translation by Eric Lendvai with author approval)

For complete attribution details, see [`CREDITS.md`](./CREDITS.md)

---

© 2025 Eric Lendvai & Byron Henderson (MayaPOS) — Licensed under [CC BY-NC-SA 4.0](./LICENSE)


