# Compile Cobol — Enterprise Legacy Modernization

**Six IBM languages. One platform. Zero runtime fees.**

Compile Cobol builds transpilers that convert IBM mainframe and midrange source code into human-readable, human-maintainable C++17 and Java 21 — not emulated, not wrapped, not interpreted. The generated code compiles with standard toolchains (MSVC, GCC, Clang, JDK 21) and runs on customer-owned infrastructure with no per-core, per-transaction, or per-CPU-hour fees.

---

## Products

### WebXCOBOL — Enterprise Legacy Transpiler Suite

| Division | Source Language | Target | Status |
|----------|---------------|--------|--------|
| I | **COBOL** | C++17 + Java 21 | 219/219 C++ &middot; 203/203 Java &middot; 426/426 NIST-85 |
| III | **RPG IV** | Java 21 | 306/306 tests &middot; fixed/free/full-free format |
| IV | **HLASM** | C++17 + Java 21 | 250/250 tests &middot; semantic lifter, not emulator |
| V | **Schema Migrator** | SQL DDL + data load | PostgreSQL, MySQL, Oracle, MSSQL, DB2i, ANSI |
| VI | **PL/I** | C++17 + Java 21 | 156/156 tests |
| VII | **CL** | Java + Bash | 50/50 tests |
| VIII | **Source Import** | Auto-detect + EBCDIC decode | 11 source types, 8 codepages |
| IX | **JCL** | Native execution engine | JOB/EXEC/DD/PROC/GDG/COND |

**Total: 1,610+ automated tests. Zero failures.**

### Subsystem Runtime

Every subsystem a mainframe program depends on — implemented and tested:

- **EXEC SQL / DB2** — cursors, dynamic SQL, PREPARE/EXECUTE, SQLCA, ODBC + JDBC
- **EXEC CICS** — 30+ commands: file control, BMS SEND/RECEIVE MAP, queues, LINK, ENQ/DEQ, HANDLE CONDITION
- **IMS DB/DC** — full DL/I: GU/GN/GHU/ISRT/REPL/DLET, PCB status codes, SSA command codes
- **IBM MQ** — MQCONN/MQOPEN/MQPUT/MQGET with reason code emulation
- **VSAM** — in-memory B-tree KSDS/RRDS/ESDS with primary + alternate keys
- **Report Writer** — INITIATE/GENERATE/TERMINATE, control breaks, SUM accumulators
- **RACF** — two-tier security emulation with SHA-256 hashed ACL store

### Compliance (Built-In, Not Bolted On)

| Framework | Coverage |
|-----------|----------|
| IRS Publication 1075 | FTI field masking + tokenization |
| PCI DSS v4.0 | Format-preserving tokenization vault, Luhn validation |
| HIPAA Safe Harbor | All 18 identifiers per 45 CFR 164.514(b) |
| SOX Section 404 | HMAC-SHA256 tamper-evident audit chain |
| GDPR | Right to Erasure (crypto-erase), Portability (JSON), Minimisation |
| CCPA | Opt-Out, Right to Know, Right to Delete |
| EO 14028 | CycloneDX 1.4 SBOM on every compilation |
| NIST 800-53 | Control family mapping (AC, AU, SC, SI) |
| FIPS 140-2/3 | KMS hooks for HSM integration |

### Cross-Language Bridge

Transpiled programs in any of the six languages can call programs in any other language:

```
COBOL program  →  CALL 'RPGPROG'  →  Java (RPG)  →  CALL 'PLIPROG'  →  C++ (PL/I)
```

- Java-to-Java: reflection-based dispatch
- Java-to-C++: auto-generated JNI bridge
- C++-to-Java: embedded JVM (JNI_CreateJavaVM)
- Shared WORKING-STORAGE via memory-mapped files

### HLASM: The Only Semantic Lifter

Our HLASM compiler is **not an emulator**. It maps z/Architecture instructions to equivalent C++/Java constructs:

- `MVC` → `memcpy` (with ripple-fill detection for overlapping moves)
- `AP/SP/MP/DP` → BCD-native arithmetic (31 digits, no floating-point)
- `BCT` loops → `while` loops
- Save area boilerplate → suppressed
- Result: **human-readable C++ that a developer can maintain**

---

## Why This Matters

| | AWS Blu Age | Micro Focus | Heirloom | **Compile Cobol** |
|---|---|---|---|---|
| Languages | 1 (COBOL) | 1 (COBOL) | 2 (COBOL + PL/I) | **6** |
| HLASM | No | No | No | **Yes (semantic lift)** |
| Runtime cost | $0.31/core/hr | License fee | License fee | **$0** |
| Output readability | Low | N/A (emulator) | Medium | **High** |
| Compliance built-in | No | No | No | **6 frameworks** |
| NIST-85 certified | Unknown | Partial | Unknown | **426/426 (100%)** |

**5-year TCO on 5M LOC portfolio: AWS Blu Age = ~$50M. Compile Cobol = ~$50K.**

---

## Architecture

```
Source Code (COBOL/RPG/PL/I/HLASM/CL/JCL)
    │
    ▼
┌─────────────────────────────────┐
│  WebXCOBOL Compiler Pipeline    │
│  Lexer → Parser → AST → Codegen│
│  (119,000 lines of C)           │
└─────────────┬───────────────────┘
              │
    ┌─────────┴─────────┐
    ▼                   ▼
  C++17              Java 21
  (libwebxcob.h)     (RpgProgram.java, CobField.java)
    │                   │
    ▼                   ▼
  MSVC/GCC/Clang     JDK 21
    │                   │
    ▼                   ▼
  Native binary      .class / .jar
  ($0 runtime)       ($0 runtime)
```

---

## Quick Start

```bash
# COBOL → C++
./webx -M program.cbl
g++ -std=c++17 -I src/COBOL program.cpp -o program

# COBOL → Java
./webx -J program.cbl
javac -cp java_build program.java

# RPG IV → Java
./rpg400 program.rpgle
javac -cp java_build Program.java

# HLASM → C++
./asmx program.mlc
g++ -std=c++17 program.cpp -o program
```

---

## Test Validation

```
COBOL C++:    219/219  (100%)
COBOL Java:   203/203  (100%)
NIST-85:      426/426  (100%)
RPG IV:       306/306  (100%)
PL/I:         156/156  (100%)
HLASM:        250/250  (100%)
CL:            50/50   (100%)
────────────────────────────────
Total:      1,610/1,610 (100%)
```

---

### WebXPHP — FiveWin/Harbour to PHP Transpiler

Separate product. Converts desktop FiveWin `.prg` applications to browser-based PHP — same API, standard hosting, zero Harbour dependency. See [WebXPHP docs](docs/) and the [MayaPOS reference implementation](https://github.com/mayapos/WebX).

---

## Contact

- **Website**: [compilecobol.com](https://compilecobol.com) &middot; [xbasephp.com](https://xbasephp.com)
- **Email**: mayabuilders@gmail.com
- **GitHub**: [github.com/mayapos](https://github.com/mayapos)

---

*Built by Bayron Landaverry / Compile Cobol. 119,000 lines of compiler. One engineer. Six languages. Zero runtime fees.*
