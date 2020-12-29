uses ABCObjects, graphabc, System.Windows.Forms,System.Drawing;

var idle_back_color := rgb(25,25,25);
var active_back_color := rgb(65,65,65);

const idle_font_color = clwhite;
const active_font_color = clwhite;

const text_scale = 1.0;

procedure generate_arrow_btn(name:string;text_color:color; back_color:color; t:string; dir:string);
begin
var butt:=new RectangleABC(0,0,101,101);
butt.Bordered:=false;
//butt.FontName:='steelfish';
butt.TextScale := 1.0;
butt.FontColor := text_color;
if dir='l' then butt.Text := '<' else butt.Text := '>';
butt.Color:=back_color;
butt.RedrawNow();
var Bm := new Bitmap(100, 100); 
var Gr := Graphics.FromImage(Bm); 
Gr.CopyFromScreen(0, 0, 0, 0, Bm.Size); 
Bm.Save(getcurrentdir()+'/'+name+'_'+t+'.png');
end;

procedure generate_text_btn(text:string; text_color:color; back_color:color; t:string; scale:real:=text_scale);
begin
var butt:=new RectangleABC(0,0,401,121);
butt.Bordered:=false;
butt.FontName:='steelfish';
butt.TextScale := scale;
butt.FontColor := text_color;
butt.Text := text;
butt.Color:=back_color;
butt.RedrawNow();
var Bm := new Bitmap(400, 120); 
var Gr := Graphics.FromImage(Bm); 
Gr.CopyFromScreen(0, 0, 0, 0, Bm.Size); 
Bm.Save(getcurrentdir()+'/'+text+'_'+t+'.png');
end;

procedure generate_text_btn_active_idle(text:string);
begin
generate_text_btn(text, active_font_color, active_back_color, 'active');
generate_text_btn(text, idle_font_color, idle_back_color, 'idle');
end;

procedure generate_arrow_btn_active_idle(text:string; dir:string);
begin
generate_arrow_btn(text,idle_font_color,idle_back_color,'idle', dir);
generate_arrow_btn(text,active_font_color, active_back_color,'active', dir);
end;

begin
window.Init(-8,-30,400,120,clwhite);
generate_text_btn_active_idle('endless');
generate_text_btn_active_idle('timed');
generate_text_btn_active_idle('exit');
generate_text_btn_active_idle('back');
generate_text_btn_active_idle('start');
generate_text_btn_active_idle('results');
generate_text_btn_active_idle('ok');
generate_arrow_btn_active_idle('leftArrow','l');
generate_arrow_btn_active_idle('rightArrow','r');
halt();
end.