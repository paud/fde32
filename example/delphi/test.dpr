program test;

{$APPTYPE CONSOLE}

uses
  SysUtils,
  untFDE in '..\..\bindings\Delphi\untFDE.pas',
  untFDE32 in '..\..\bindings\Delphi\untFDE32.pas',
  untFDE64 in '..\..\bindings\Delphi\untFDE64.pas';

var
  cmd:TFDES;
  a:Pointer;

function getoffset:Pointer;
asm
{$IFDEF WIN32}
  mov eax,offset getoffset
{$ENDIF}
{$IFDEF WIN64}
  mov rax,offset getoffset
{$ENDIF}
end;

begin
  a:=getoffset;
  FDEDecode(a,cmd);
  Writeln(IntToStr(cmd.len));
  Readln;
end.
