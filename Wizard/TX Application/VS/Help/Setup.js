//=============================================================================
// Setup program for the TX Library Visual Studio .NET Help - (c) Ded, 2006
//=============================================================================

var IgnoreErrors = true;
var DebugMode    = false;

var Action       = "install";

//-----------------------------------------------------------------------------

var Shell        = WScript.CreateObject ("WScript.Shell");
var FS           = WScript.CreateObject ("Scripting.FileSystemObject");

main_IgnoreErrors (WScript.Arguments.length, WScript.Arguments);

//-----------------------------------------------------------------------------

function main_IgnoreErrors (argc, argv)
    {
    try { main (argc, argv); }
    catch (e) {}
    }

//-----------------------------------------------------------------------------

function main (argc, argv)
    {
    if (argc > 0 && argv (0) == "/debug")     DebugMode  = true;
    if (argc > 0 && argv (0) == "/uninstall") Action = "uninstall";

    try
        {
        if (Action ==   "install") Shell.Run ("h2reg.exe -r -m cmdfile=TXLibReg.ini");
        if (Action == "uninstall") Shell.Run ("h2reg.exe -u -m cmdfile=TXLibReg.ini");
        }

    catch (e)
        {
        throw Error (e, "Cannot register/unregister help");
        }
    }

//-----------------------------------------------------------------------------

function Error (e, msg)
    {
    var descr = "";
    if (e != null && 
        e.description != null &&
        e.description.length != 0) descr = e.description;

    if (msg != "" && descr != "") msg += ": ";
    msg += descr;

    if (!IgnoreErrors)
        Echo ("ERROR: " + msg);

    return e;
    }

//-----------------------------------------------------------------------------

function Debug (msg)
    {
    if (DebugMode) Echo (msg);
    }

//-----------------------------------------------------------------------------

function Echo (msg)
    {
    WScript.Echo (msg + "    ");
    }
