# WebX Runtime Libraries - PHP Function Stubs

**Last Updated:** 2026-02-05
**Total Functions:** 2,000+
**Status:** Production Ready

---

## Overview

WebX provides comprehensive PHP implementations of Harbour/xBase runtime functions. These stubs enable transpiled WebX applications to run in pure PHP environments without requiring Harbour binaries.

**Key Benefits:**
- Run on any PHP 8.x+ server
- No Harbour installation required
- Compatible with shared hosting
- Full xBase functionality in web environment

---

## Library Summary

| Library | File | Functions | Description |
|---------|------|-----------|-------------|
| **Harbour RTL** | `harbour_rtl_stubs.php` | 792 | Core runtime functions |
| **RTL Addon** | `harbour_functions_addon.php` | 50+ | Extended RTL functions |
| **Clipper Tools** | `harbour_ct_stubs.php` | 200+ | hbct contrib library |
| **NanForum** | `harbour_nf_stubs.php` | 100+ | hbnf contrib library |
| **PCRE Regex** | `harbour_regex_stubs.php` | 40+ | Regular expressions |
| **TIP Protocol** | `harbour_tip_stubs.php` | 50+ | HTTP/SMTP/FTP clients |
| **FiveWin Compat** | `fivewin_stubs.php` | 300+ | FiveWin API layer |
| **TOTAL** | - | **~2,000+** | - |

---

## 1. Harbour RTL (harbour_rtl_stubs.php)

The core runtime library with 792 functions covering all essential xBase operations.

### String Functions

| Function | Description | Example |
|----------|-------------|---------|
| `ALLTRIM(cStr)` | Remove leading/trailing spaces | `ALLTRIM("  Hi  ")` → `"Hi"` |
| `LTRIM(cStr)` | Remove leading spaces | `LTRIM("  Hi")` → `"Hi"` |
| `RTRIM(cStr)` | Remove trailing spaces | `RTRIM("Hi  ")` → `"Hi"` |
| `UPPER(cStr)` | Convert to uppercase | `UPPER("hello")` → `"HELLO"` |
| `LOWER(cStr)` | Convert to lowercase | `LOWER("HELLO")` → `"hello"` |
| `LEFT(cStr, n)` | Get leftmost n characters | `LEFT("Hello", 2)` → `"He"` |
| `RIGHT(cStr, n)` | Get rightmost n characters | `RIGHT("Hello", 2)` → `"lo"` |
| `SUBSTR(cStr, n, len)` | Extract substring | `SUBSTR("Hello", 2, 3)` → `"ell"` |
| `AT(cSearch, cStr)` | Find substring position | `AT("l", "Hello")` → `3` |
| `RAT(cSearch, cStr)` | Find last occurrence | `RAT("l", "Hello")` → `4` |
| `REPLICATE(cStr, n)` | Repeat string n times | `REPLICATE("*", 5)` → `"*****"` |
| `SPACE(n)` | Create n spaces | `SPACE(10)` → 10 spaces |
| `PADR(cStr, n, cPad)` | Right-pad to length | `PADR("Hi", 5)` → `"Hi   "` |
| `PADL(cStr, n, cPad)` | Left-pad to length | `PADL("Hi", 5)` → `"   Hi"` |
| `PADC(cStr, n, cPad)` | Center-pad to length | `PADC("Hi", 6)` → `"  Hi  "` |
| `STRTRAN(cStr, cOld, cNew)` | Replace all occurrences | `STRTRAN("aa", "a", "b")` → `"bb"` |
| `STUFF(cStr, n, len, cNew)` | Insert/replace | `STUFF("ABCD", 2, 1, "XX")` → `"AXXCD"` |
| `TRANSFORM(x, cPic)` | Format with picture | `TRANSFORM(1234.5, "@E 9,999.99")` |
| `CHR(n)` | ASCII code to character | `CHR(65)` → `"A"` |
| `ASC(c)` | Character to ASCII code | `ASC("A")` → `65` |
| `LEN(x)` | String/array length | `LEN("Hello")` → `5` |

### Array Functions

| Function | Description | Example |
|----------|-------------|---------|
| `AADD(aArr, xVal)` | Append element | `AADD(a, "new")` |
| `ASIZE(aArr, n)` | Resize array | `ASIZE(a, 10)` |
| `ADEL(aArr, n)` | Delete element | `ADEL(a, 2)` |
| `AINS(aArr, n)` | Insert element | `AINS(a, 1)` |
| `AFILL(aArr, xVal)` | Fill with value | `AFILL(a, 0)` |
| `ACLONE(aArr)` | Deep copy array | `b := ACLONE(a)` |
| `ACOPY(aSrc, aDst)` | Copy elements | `ACOPY(a, b)` |
| `ASCAN(aArr, xVal)` | Find element | `ASCAN(a, "test")` → position |
| `ASORT(aArr)` | Sort array | `ASORT(a)` |
| `AEVAL(aArr, bBlock)` | Evaluate block for each | `AEVAL(a, {|x| QOut(x)})` |
| `ATAIL(aArr)` | Get last element | `ATAIL({1,2,3})` → `3` |
| `ARRAY(n)` | Create array of size n | `a := ARRAY(10)` |

### Date Functions

| Function | Description | Example |
|----------|-------------|---------|
| `DATE()` | Current date | `DATE()` → current date |
| `CTOD(cDate)` | String to date | `CTOD("01/15/2026")` |
| `DTOC(dDate)` | Date to string | `DTOC(DATE())` |
| `DTOS(dDate)` | Date to YYYYMMDD | `DTOS(DATE())` → `"20260205"` |
| `STOD(cDate)` | YYYYMMDD to date | `STOD("20260205")` |
| `DOW(dDate)` | Day of week (1-7) | `DOW(DATE())` |
| `DOM(dDate)` | Day of month | `DOM(DATE())` |
| `DOY(dDate)` | Day of year | `DOY(DATE())` |
| `CDOW(dDate)` | Day name | `CDOW(DATE())` → `"Wednesday"` |
| `CMONTH(dDate)` | Month name | `CMONTH(DATE())` → `"February"` |
| `YEAR(dDate)` | Year number | `YEAR(DATE())` → `2026` |
| `MONTH(dDate)` | Month number | `MONTH(DATE())` → `2` |
| `DAY(dDate)` | Day number | `DAY(DATE())` → `5` |
| `TIME()` | Current time string | `TIME()` → `"14:30:25"` |
| `SECONDS()` | Seconds since midnight | `SECONDS()` → `52225.5` |
| `ELAPTIME(cStart, cEnd)` | Elapsed time | `ELAPTIME("08:00:00", "17:30:00")` |

### Math Functions

| Function | Description | Example |
|----------|-------------|---------|
| `ABS(n)` | Absolute value | `ABS(-5)` → `5` |
| `INT(n)` | Integer part | `INT(3.7)` → `3` |
| `ROUND(n, dec)` | Round to decimals | `ROUND(3.456, 2)` → `3.46` |
| `SQRT(n)` | Square root | `SQRT(16)` → `4` |
| `EXP(n)` | e to power n | `EXP(1)` → `2.718...` |
| `LOG(n)` | Natural logarithm | `LOG(10)` → `2.302...` |
| `LOG10(n)` | Base-10 logarithm | `LOG10(100)` → `2` |
| `MOD(n, div)` | Modulo | `MOD(10, 3)` → `1` |
| `MIN(a, b)` | Minimum value | `MIN(5, 3)` → `3` |
| `MAX(a, b)` | Maximum value | `MAX(5, 3)` → `5` |

### Type Functions

| Function | Description | Example |
|----------|-------------|---------|
| `VALTYPE(x)` | Get type code | `VALTYPE("Hi")` → `"C"` |
| `TYPE(cVar)` | Get variable type | `TYPE("cName")` |
| `EMPTY(x)` | Check if empty | `EMPTY("")` → `.T.` |
| `NIL` | Null value | `x := NIL` |
| `VAL(cStr)` | String to number | `VAL("123.45")` → `123.45` |
| `STR(n, w, d)` | Number to string | `STR(123.45, 8, 2)` |
| `HB_VALTOSTR(x)` | Any value to string | `HB_VALTOSTR({1,2})` |

### I/O Functions

| Function | Description | Example |
|----------|-------------|---------|
| `QOUT(...)` | Output with newline | `QOUT("Hello")` |
| `QQOUT(...)` | Output without newline | `QQOUT("Hello")` |
| `OUTSTD(c)` | Output to stdout | `OUTSTD(cHTML)` |
| `OUTERR(c)` | Output to stderr | `OUTERR("Error!")` |
| `INKEY(n)` | Wait for keypress | `INKEY(0)` |
| `MEMOREAD(cFile)` | Read file to string | `c := MEMOREAD("data.txt")` |
| `MEMOWRIT(cFile, c)` | Write string to file | `MEMOWRIT("out.txt", cData)` |

---

## 2. Clipper Tools (harbour_ct_stubs.php)

Extended string, date, and math functions from the hbct contrib library (200+ functions).

### Advanced String Functions

| Function | Description | Example |
|----------|-------------|---------|
| `ADDASCII(c, n)` | Add to ASCII value | `ADDASCII("A", 1)` → `"B"` |
| `ATNUM(cSrch, cStr, n)` | Find nth occurrence | `ATNUM(".", "a.b.c", 2)` → `4` |
| `CHARREM(cChars, cStr)` | Remove characters | `CHARREM("aeiou", "Hello")` → `"Hll"` |
| `CHARSWAP(cStr)` | Swap adjacent chars | `CHARSWAP("ABCD")` → `"BADC"` |
| `CHARONE(cChars, cStr)` | Remove duplicate chars | `CHARONE(" ", "a  b")` → `"a b"` |
| `WORDTOCHAR(cDel, cStr)` | Replace delimiters | `WORDTOCHAR(",", "a,b,c")` → `"a b c"` |
| `PADLEFT(c, n, cPad)` | Left pad string | `PADLEFT("5", 3, "0")` → `"005"` |
| `PADRIGHT(c, n, cPad)` | Right pad string | `PADRIGHT("5", 3, "0")` → `"500"` |
| `POSALPHA(cStr)` | First alpha position | `POSALPHA("123ABC")` → `4` |
| `POSRANGE(c1, c2, cStr)` | First in range | `POSRANGE("A", "Z", "123ABC")` → `4` |
| `RANGEREPL(c1, c2, cStr, cNew)` | Replace range | Replaces chars in range |
| `TOKENINIT(cStr, cDel)` | Initialize tokenizer | Token parsing setup |
| `TOKENNEXT()` | Get next token | Returns next token |
| `TOKENNUM()` | Get token count | Returns token count |

### Date Functions

| Function | Description | Example |
|----------|-------------|---------|
| `BOM(dDate)` | Beginning of month | `BOM(DATE())` → first day |
| `EOM(dDate)` | End of month | `EOM(DATE())` → last day |
| `BOQ(dDate)` | Beginning of quarter | Quarter start date |
| `EOQ(dDate)` | End of quarter | Quarter end date |
| `BOY(dDate)` | Beginning of year | `BOY(DATE())` → Jan 1 |
| `EOY(dDate)` | End of year | `EOY(DATE())` → Dec 31 |
| `ADDMONTH(dDate, n)` | Add months | `ADDMONTH(DATE(), 3)` |
| `WOM(dDate)` | Week of month | `WOM(DATE())` → 1-5 |
| `WEEK(dDate)` | Week of year | `WEEK(DATE())` → 1-52 |
| `QUARTER(dDate)` | Quarter number | `QUARTER(DATE())` → 1-4 |
| `ISLEAP(nYear)` | Check leap year | `ISLEAP(2024)` → `.T.` |
| `DAYSINMONTH(nMonth, nYear)` | Days in month | `DAYSINMONTH(2, 2024)` → `29` |

### Math Functions

| Function | Description | Example |
|----------|-------------|---------|
| `CEILING(n)` | Round up | `CEILING(4.2)` → `5` |
| `FLOOR(n)` | Round down | `FLOOR(4.8)` → `4` |
| `SIGN(n)` | Sign of number | `SIGN(-5)` → `-1` |
| `FACT(n)` | Factorial | `FACT(5)` → `120` |
| `MANTISSA(n)` | Mantissa part | `MANTISSA(123.456)` |
| `EXPONENT(n)` | Exponent part | `EXPONENT(123.456)` |

### Bit Functions

| Function | Description | Example |
|----------|-------------|---------|
| `NUMAND(n1, n2)` | Bitwise AND | `NUMAND(12, 10)` → `8` |
| `NUMOR(n1, n2)` | Bitwise OR | `NUMOR(12, 10)` → `14` |
| `NUMXOR(n1, n2)` | Bitwise XOR | `NUMXOR(12, 10)` → `6` |
| `NUMNOT(n)` | Bitwise NOT | `NUMNOT(0)` → `-1` |
| `NUMROL(n, bits)` | Rotate left | Bit rotation |
| `NUMMIR(n)` | Mirror bits | Bit reversal |

---

## 3. NanForum Library (harbour_nf_stubs.php)

Utility functions from the hbnf contrib library (100+ functions).

### Array Functions

| Function | Description | Example |
|----------|-------------|---------|
| `FT_ASUM(aArr)` | Sum array elements | `FT_ASUM({1,2,3,4,5})` → `15` |
| `FT_AAVG(aArr)` | Average of array | `FT_AAVG({2,4,6,8,10})` → `6` |
| `FT_AMIN(aArr)` | Minimum value | `FT_AMIN({5,3,8,1,9})` → `1` |
| `FT_AMAX(aArr)` | Maximum value | `FT_AMAX({5,3,8,1,9})` → `9` |
| `FT_AMEDIAN(aArr)` | Median value | `FT_AMEDIAN({1,3,5,7,9})` → `5` |
| `FT_AREVERSE(aArr)` | Reverse array | `FT_AREVERSE({1,2,3})` → `{3,2,1}` |
| `FT_ASHUFFLE(aArr)` | Shuffle randomly | Random order |

### Conversion Functions

| Function | Description | Example |
|----------|-------------|---------|
| `FT_NTOW(n)` | Number to words | `FT_NTOW(123)` → `"One Hundred..."` |
| `FT_D2E(n, base)` | Decimal to other base | `FT_D2E(255, 16)` → `"FF"` |
| `FT_E2D(c, base)` | Other base to decimal | `FT_E2D("FF", 16)` → `255` |

### Bit Functions (String-based)

| Function | Description | Example |
|----------|-------------|---------|
| `FT_BITSET(cByte, nBit)` | Set bit | `FT_BITSET(CHR(0), 3)` → `CHR(8)` |
| `FT_BITCLR(cByte, nBit)` | Clear bit | Clear specific bit |
| `FT_BITTOG(cByte, nBit)` | Toggle bit | Toggle specific bit |
| `FT_ISBIT(cByte, nBit)` | Test bit | `FT_ISBIT(CHR(8), 3)` → `.T.` |

### String Functions

| Function | Description | Example |
|----------|-------------|---------|
| `FT_PROPER(cStr)` | Proper case | `FT_PROPER("hello WORLD")` → `"Hello World"` |
| `FT_BYTEAND(c1, c2)` | Byte AND | Bitwise AND on bytes |
| `FT_BYTEOR(c1, c2)` | Byte OR | Bitwise OR on bytes |
| `FT_BYTEXOR(c1, c2)` | Byte XOR | Bitwise XOR on bytes |
| `FT_BYTENOT(c)` | Byte NOT | Bitwise NOT on byte |

---

## 4. PCRE Regex (harbour_regex_stubs.php)

Regular expression functions using PHP's PCRE engine (40+ functions).

### Pattern Matching

| Function | Description | Example |
|----------|-------------|---------|
| `HB_REGEXCOMP(pattern)` | Compile regex | `r := HB_REGEXCOMP("[0-9]+")` |
| `HB_REGEXMATCH(pat, str)` | Test if matches | `HB_REGEXMATCH("[0-9]+", "abc123")` → `.T.` |
| `HB_REGEXLIKE(pat, str)` | Full string match | Anchored match |
| `HB_REGEXHAS(pat, str)` | Contains match | Same as REGEXMATCH |

### Find/Extract

| Function | Description | Example |
|----------|-------------|---------|
| `HB_REGEXFIND(pat, str)` | Find first match | `HB_REGEXFIND("[0-9]+", "abc123")` → `"123"` |
| `HB_REGEXFINDALL(pat, str)` | Find all matches | Returns array of matches |
| `HB_REGEXALL(pat, str)` | All with groups | Returns array with captures |
| `HB_REGEXATX(pat, str)` | Position and length | Returns `{position, length}` |

### Replace/Split

| Function | Description | Example |
|----------|-------------|---------|
| `HB_REGEXSUB(pat, str, repl)` | Replace all | `HB_REGEXSUB("[0-9]", "a1b2", "X")` → `"aXbX"` |
| `HB_REGEXREPLACE(...)` | Alias for REGEXSUB | Same as above |
| `HB_REGEXSPLIT(pat, str)` | Split by pattern | `HB_REGEXSPLIT("[,;]", "a,b;c")` → `{"a","b","c"}` |

### Utilities

| Function | Description | Example |
|----------|-------------|---------|
| `HB_REGEXESCAPE(str)` | Escape special chars | `HB_REGEXESCAPE("a.b")` → `"a\.b"` |
| `HB_REGEXCOUNT(pat, str)` | Count matches | `HB_REGEXCOUNT("[aeiou]", "hello")` → `2` |
| `HB_REGEXTEST(pat)` | Validate pattern | `.T.` if valid regex |

### Character Class Helpers

| Function | Description | Example |
|----------|-------------|---------|
| `HB_ISALPHA(c)` | Is alphabetic | `HB_ISALPHA("A")` → `.T.` |
| `HB_ISDIGIT(c)` | Is digit | `HB_ISDIGIT("5")` → `.T.` |
| `HB_ISALNUM(c)` | Is alphanumeric | `HB_ISALNUM("A")` → `.T.` |
| `HB_ISUPPER(c)` | Is uppercase | `HB_ISUPPER("A")` → `.T.` |
| `HB_ISLOWER(c)` | Is lowercase | `HB_ISLOWER("a")` → `.T.` |
| `HB_ISSPACE(c)` | Is whitespace | `HB_ISSPACE(" ")` → `.T.` |
| `HB_ISPRINT(c)` | Is printable | `HB_ISPRINT("A")` → `.T.` |

---

## 5. TIP Protocol Library (harbour_tip_stubs.php)

Internet protocol clients for HTTP, SMTP, and FTP (50+ functions/methods).

### TIPClientHTTP Class

HTTP client for web requests:

```harbour
// Create client
oHttp := TIP_HTTP("https://api.example.com")

// Configure
oHttp:AddHeader("Content-Type", "application/json")
oHttp:SetMethod("POST")
oHttp:SetPostData('{"name": "test"}')

// Execute
IF oHttp:Open()
   cResponse := oHttp:ReadAll()
   oHttp:Close()
ENDIF
```

**Methods:**
- `New(cUrl)` - Create client with URL
- `Open()` - Connect to server
- `Close()` - Close connection
- `Get(cPath)` - GET request
- `Post(cPath, cData)` - POST request
- `Put(cPath, cData)` - PUT request
- `Delete(cPath)` - DELETE request
- `ReadAll()` - Read response body
- `AddHeader(cName, cValue)` - Add HTTP header
- `SetMethod(cMethod)` - Set HTTP method
- `SetPostData(cData)` - Set request body
- `Download(cUrl, cFile)` - Download to file

### TIPClientSMTP Class

Email sending with SMTP:

```harbour
oSmtp := TIP_SMTP("smtp.example.com", 587)
oSmtp:SetAuth("user", "password")
oSmtp:SetFrom("sender@example.com", "Sender Name")
oSmtp:AddTo("recipient@example.com")
oSmtp:SetSubject("Hello!")
oSmtp:SetBody("Email body text")
oSmtp:Send()
```

**Methods:**
- `New(cHost, nPort)` - Create client
- `SetAuth(cUser, cPass)` - Set credentials
- `SetFrom(cEmail, cName)` - Set sender
- `AddTo(cEmail)` - Add recipient
- `AddCc(cEmail)` - Add CC recipient
- `AddBcc(cEmail)` - Add BCC recipient
- `SetSubject(cSubject)` - Set subject
- `SetBody(cBody)` - Set body text
- `SetHtmlBody(cHtml)` - Set HTML body
- `AddAttachment(cFile)` - Add attachment
- `Send()` - Send email

### TIPClientFTP Class

FTP file operations:

```harbour
oFtp := TIP_FTP("ftp.example.com")
oFtp:SetAuth("user", "password")
IF oFtp:Open()
   oFtp:ChangeDir("/uploads")
   oFtp:Upload("local.txt", "remote.txt")
   aFiles := oFtp:ListDir()
   oFtp:Close()
ENDIF
```

**Methods:**
- `New(cHost, nPort)` - Create client
- `SetAuth(cUser, cPass)` - Set credentials
- `Open()` - Connect
- `Close()` - Disconnect
- `Upload(cLocal, cRemote)` - Upload file
- `Download(cRemote, cLocal)` - Download file
- `ListDir()` - List directory
- `ChangeDir(cDir)` - Change directory
- `MakeDir(cDir)` - Create directory
- `DeleteFile(cFile)` - Delete file
- `Rename(cOld, cNew)` - Rename file

### Quick Helper Functions

| Function | Description | Example |
|----------|-------------|---------|
| `TIP_HTTP(url)` | Create HTTP client | `o := TIP_HTTP("https://...")` |
| `TIP_SMTP(host, port)` | Create SMTP client | `o := TIP_SMTP("smtp...", 587)` |
| `TIP_FTP(host, port)` | Create FTP client | `o := TIP_FTP("ftp...", 21)` |
| `TIP_GET(url)` | Quick GET request | `c := TIP_GET("https://...")` |
| `TIP_POST(url, data)` | Quick POST request | `c := TIP_POST(url, cJson)` |
| `TIP_DOWNLOAD(url, file)` | Download file | `TIP_DOWNLOAD(url, "file.zip")` |
| `TIP_MAIL(...)` | Quick send email | Send email in one call |
| `TIP_URLENCODE(str)` | URL encode | `TIP_URLENCODE("hello world")` |
| `TIP_URLDECODE(str)` | URL decode | `TIP_URLDECODE("hello+world")` |
| `TIP_HTMLENCODE(str)` | HTML encode | `TIP_HTMLENCODE("<b>")` → `"&lt;b&gt;"` |
| `TIP_HTMLDECODE(str)` | HTML decode | `TIP_HTMLDECODE("&lt;b&gt;")` → `"<b>"` |
| `TIP_BASE64ENCODE(str)` | Base64 encode | `TIP_BASE64ENCODE("test")` → `"dGVzdA=="` |
| `TIP_BASE64DECODE(str)` | Base64 decode | `TIP_BASE64DECODE("dGVzdA==")` → `"test"` |
| `TIP_JSON(data)` | Encode to JSON | `TIP_JSON({"a": 1})` → `'{"a":1}'` |
| `TIP_JSONPARSE(str)` | Parse JSON | `TIP_JSONPARSE('{"a":1}')` → hash |

---

## 6. FiveWin Compatibility (fivewin_stubs.php)

FiveWin API compatibility layer (300+ functions/classes).

### Message Box Functions

| Function | Description | Example |
|----------|-------------|---------|
| `MSGINFO(cMsg, cTitle)` | Info message | `MSGINFO("Done!", "Info")` |
| `MSGSTOP(cMsg, cTitle)` | Error message | `MSGSTOP("Error!", "Stop")` |
| `MSGALERT(cMsg, cTitle)` | Warning message | `MSGALERT("Warning!")` |
| `MSGYESNO(cMsg, cTitle)` | Yes/No dialog | `IF MSGYESNO("Continue?")` |
| `MSGRETRYCANCEL(...)` | Retry/Cancel | User choice dialog |
| `MSGWAIT(cMsg, cTitle, n)` | Timed message | Auto-close after n seconds |

### Input Dialogs

| Function | Description | Example |
|----------|-------------|---------|
| `MSGGET(cPrompt, cTitle, cDefault)` | Text input | `c := MSGGET("Name?")` |
| `MSGMULTIGET(aPrompts)` | Multiple inputs | Array of values |
| `MSGSELECT(aItems)` | Selection list | Selected item |
| `MSGDATE(cTitle)` | Date picker | Selected date |
| `MSGRADIO(aOptions)` | Radio options | Selected option |
| `MSGLIST(aItems)` | List selection | Multiple select |

### File Dialogs (Web Adapted)

| Function | Description | Example |
|----------|-------------|---------|
| `CGETFILE(cFilter, cTitle)` | Open file dialog | Returns filename |
| `CGETDIR(cTitle)` | Folder dialog | Returns path |
| `CPUTFILE(cFilter, cTitle)` | Save file dialog | Returns filename |
| `CSAVEFILE(cFilter, cTitle)` | Save as dialog | Returns filename |
| `CGETCOLOR()` | Color picker | Returns color value |
| `CGETFONT()` | Font picker | Returns font info |

### Color Functions

| Function | Description | Example |
|----------|-------------|---------|
| `NRGB(r, g, b)` | Create RGB color | `NRGB(255, 0, 0)` → red |
| `GETRED(nColor)` | Extract red | `GETRED(nColor)` → 0-255 |
| `GETGREEN(nColor)` | Extract green | `GETGREEN(nColor)` → 0-255 |
| `GETBLUE(nColor)` | Extract blue | `GETBLUE(nColor)` → 0-255 |
| `COLORTORGB(nColor)` | To RGB array | `{r, g, b}` |
| `COLORTOHEX(nColor)` | To hex string | `"#FF0000"` |

### System Functions

| Function | Description | Example |
|----------|-------------|---------|
| `SYSREFRESH()` | Refresh UI | Redraw controls |
| `CURSORWAIT()` | Show wait cursor | Loading state |
| `CURSORARROW()` | Show arrow cursor | Normal state |
| `WINEXEC(cCmd)` | Execute program | Opens calculator, etc. |
| `SHELLEXECUTE(...)` | Shell execute | Open files/URLs |
| `WAITRUN(cCmd)` | Run and wait | Execute synchronously |
| `GETENV(cVar)` | Get environment | `GETENV("PATH")` |
| `SETENV(cVar, cVal)` | Set environment | `SETENV("DEBUG", "1")` |

### Constants

**Window Styles:**
- `WS_OVERLAPPED`, `WS_POPUP`, `WS_CHILD`, `WS_VISIBLE`, `WS_BORDER`, etc.

**Message Box Types:**
- `MB_OK`, `MB_YESNO`, `MB_OKCANCEL`, `MB_ICONERROR`, `MB_ICONQUESTION`, etc.

**Virtual Keys:**
- `VK_RETURN`, `VK_ESCAPE`, `VK_TAB`, `VK_F1`-`VK_F12`, etc.

**Colors:**
- `CLR_BLACK`, `CLR_WHITE`, `CLR_RED`, `CLR_GREEN`, `CLR_BLUE`, `CLR_YELLOW`, etc.

**File Attributes:**
- `FA_NORMAL`, `FA_READONLY`, `FA_HIDDEN`, `FA_SYSTEM`, `FA_DIRECTORY`, etc.

### FiveWin Classes (Stubs)

| Class | Description |
|-------|-------------|
| `TTimer` | Timer control |
| `TSplitter` | Splitter control |
| `TIcon` | Icon resource |
| `TCursor` | Cursor resource |
| `TPrinter` | Print support |
| `TBar` | Toolbar |

---

## Desktop-to-Web Translation Notes

Many desktop commands have no direct web equivalent. WebX handles this through:

1. **Web Alternatives**: `WinExec("Calc")` → Browser-based calculator
2. **No-Op Stubs**: `SetCursor()` returns sensible defaults
3. **Best-Effort**: Windows dialogs → Bootstrap modals
4. **Documented Gaps**: Placeholder values maintain code flow

**Note:** Behavior may differ from desktop implementations. WebX provides *functional compatibility* rather than *exact replication*.

---

## Loading Libraries

All libraries are automatically loaded by `webx_all.php`:

```php
<?php
require_once __DIR__ . '/webxphp_classes/webx_all.php';

// Now all 2,000+ functions are available
QOUT("Hello from WebX!");
```

---

## Version History

| Date | Version | Changes |
|------|---------|---------|
| 2026-02-05 | 2.0 | Added TIP protocol library, enhanced FiveWin stubs |
| 2026-02-04 | 1.5 | Added Clipper Tools, NanForum, Regex libraries |
| 2026-01-21 | 1.0 | Initial Harbour RTL stubs (792 functions) |

---

**WebX Framework**
**Organization:** xBasePHP
**Website:** https://xBasePHP.com
