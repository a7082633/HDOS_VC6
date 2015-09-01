copy  ssse32.lib	%windir%\system
copy  ssse32.DLL	%windir%\system
copy  def32.lib 	%windir%\system32
copy  def32.DLL 	%windir%\system32
copy  Crw.lib		%windir%\system
copy  Crw.ocx		%windir%\system

%windir%\system\regsvr32 crw.ocx
