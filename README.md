# Universal Character Set Detector
A universal character set detetor from Notepad++ in C#

They did a excellent stuff in C++ at https://github.com/notepad-plus-plus/notepad-plus-plus/tree/master/PowerEditor/src/uchardet

So I build the code of uchardet to DLL and write a C# interface to use it, I think it is the best detector now, and it may helps C# coders a lot.

## Example
- Example 1 : just require the encoding type of a file or stream

```C#
internal Encoding DetectEncoding(Stream stream)
{
    return Notepadplusplus.UcharDetector.Detect(stream);
}

internal Encoding DetectEncoding(string filename)
{
    return Notepadplusplus.UcharDetector.Detect(filename);
}
```

- Example 2 : read a file in detected encoding type

```C#
internal string ReadFile(string filename)
{
    using (var fs = new FileStream(filename, FileMode.Open))
    {
        using (var sr = new StreamReader(fs, Notepadplusplus.UcharDetector.Detect(fs)))
        {
            return sr.ReadToEnd();
        }
    }
}
```

## Contact me
cxw39@foxmail.com
