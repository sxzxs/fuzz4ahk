class fuzz
{
    static all_dll_func := map("fuzz.dll" , map("rapid_fuzz_cpp_ratio", 0, "rapid_fuzz_cpp_partial_ratio", 0, "rapid_fuzz_cpp_token_ratio", 0, "rapid_fuzz_cpp_partial_token_ratio", 0,
                                 "rapid_fuzz_cpp_token_sort_ratio", 0, "rapid_fuzz_cpp_partial_token_sort_ratio", 0, "rapid_fuzz_cpp_token_set_ratio", 0, "rapid_fuzz_cpp_partial_token_set_ratio", 0))
    static load_all_dll_func()
    {
        SplitPath(A_LineFile,,&dir)
        path := "", lib_path := dir
        if(A_IsCompiled)
        {
            path := (A_PtrSize == 4) ? A_ScriptDir . "\lib\dll_32\" : A_ScriptDir . "\lib\dll_64\"
            lib_path := A_ScriptDir . "\lib"
        }
        else
            path := (A_PtrSize == 4) ? dir . "\dll_32\" : dir . "\dll_64\"
        dllcall("SetDllDirectory", "Str", path)
        for k,v in this.all_dll_func
        {
            for k1, v1 in v 
                this.all_dll_func[k][k1] := DllCall("GetProcAddress", "Ptr", DllCall("LoadLibrary", "Str", k, "Ptr"), "AStr", k1, "Ptr")
        }
        this.is_dll_load := true
        DllCall("SetDllDirectory", "Str", A_ScriptDir)
    }
    static __new() => this.load_all_dll_func()
    static __Call(Name, Params) => DllCall(this.all_dll_func["fuzz.dll"]["rapid_fuzz_cpp_" Name], "wstr", Params[1], "wstr", Params[2], "Cdecl Double")
}