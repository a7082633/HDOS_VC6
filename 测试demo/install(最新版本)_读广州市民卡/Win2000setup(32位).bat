copy  ssse32.lib	%windir%\system32
copy  ssse32.DLL	%windir%\system32
copy  def32.lib 	%windir%\system32
copy  def32.DLL 	%windir%\system32
copy  Crw.lib		%windir%\system32
copy  Crw.ocx		%windir%\system32


%windir%\system32\regsvr32 crw.ocx

pause