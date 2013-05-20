set PATH=D:\Program Files (x86)\Microsoft Visual Studio 10.0\Team Tools\Performance Tools;%PATH%
set _NT_SYMBOL_PATH=symsrv*symsrv.dll*C:\localsymbols*http://msdl.microsoft.com/download/symbols

cd /d %~dp1
mkdir profile

vsperfcmd /start:sample /output:profile\%~n1.vsp /launch:%1
vsperfcmd /shutdown
vsperfreport profile\%~n1.vsp /summary:all /output:profile

pause