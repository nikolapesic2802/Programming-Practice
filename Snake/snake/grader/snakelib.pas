unit snakelib;

interface

function get_speed : longint;
procedure ask_snake(U1 : longint; U2 : longint; var A1 : char; var A2 : char);
procedure tell_length(Len : longint);

implementation

var initialized : boolean;
	 fin, fout : text;
    
procedure initialize;
var ior : longint;

begin
assign(fin, 'gslibIN');
assign(fout, 'gslibOUT');

{$I-} reset(fin); rewrite(fout); {$I+}
ior := ioresult;
if (ior <> 0) then
  begin
  writeln(stderr, 'i/o error (gslib_iface)');
  halt(1);
  end;
  
initialized := true;
end;

function get_speed : longint;
var x : longint;
begin
  if not initialized then initialize;
	writeln(fout, 'get_speed');
	flush(fout);
	readln(fin, x);
	get_speed := x;
end;

procedure ask_snake(U1 : longint; U2 : longint; var A1 : char; var A2 : char);
var dummy : char;

begin
  if not initialized then initialize;
  
	writeln(fout, 'ask_snake');
  writeln(fout, U1);
  writeln(fout, U2);
	flush(fout);
  readln(fin, A1, dummy, A2);
end;

procedure tell_length(Len : longint);
var temp : longint;
begin
  if not initialized then initialize;
  
	writeln(fout, 'tell_length');
	writeln(fout, Len);
	flush(fout);
  readln(fin, temp); 
	halt(0);
end;

begin
initialized := false;
end.
