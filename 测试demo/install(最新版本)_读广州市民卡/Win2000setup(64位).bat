copy  ssse32.lib			%windir%\SysWOW64
copy  ssse32.DLL	                %windir%\SysWOW64
copy  def32.lib			        %windir%\SysWOW64
copy  def32.DLL	                        %windir%\SysWOW64
copy  Crw.lib	                        %windir%\SysWOW64
copy  Crw.ocx                           %windir%\SysWOW64

%windir%\SysWOW64\regsvr32 crw.ocx