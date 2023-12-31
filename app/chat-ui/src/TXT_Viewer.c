/*
 *@作者: HAH (BiliBili: iccery)
 *
 *@演示：如果字符缓冲区是:char *buf = "he\rllo,th\ris is a test.\ncan you see something here?\nIf you can see some words\n
 *                                     This test may have succeeded!\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n"
 *
 *               3种解析样式将会是这样（假设过滤'\r'）:
 *
 *       NORMAL              AUTO_BREAKLINE           CONSOLE_PRINT
 * +----------------+      +----------------+      +----------------+ 
 * |hello, this is a|      |hello, this is a|      |5               |
 * |can you see some|      |test. can you se|      |6               |
 * |If you can some |      |e something here|      |7               |
 * |This test may ha|      |If you can see s|      |8               |
 * |1               |      |ome words       |      |9               |
 * |2               |      |This test may ha|      |10              |
 * +----------------+      +----------------+      +----------------+ 
 *@功能：
 *    1, 三种解析器         2，CONSOLE_PRINT滚动线性动画
 *    3, 输入窗口跟踪        4，窗口设置大小
 *    5, 窗口设置位置        6，窗口分割字符
 *    7, 键盘输入模式        8，改变字符缓冲源
 *    9, 窗口跟踪线性动画    10，特殊字符过滤
 *    11, 清空字符缓存      12，初始化打印
 *    13, 全局动画开关
 *@机制：
 *       程序采用循环存储，以换行符结尾的一段连续字符视为一个‘换行行’，当存储位置大于显示开始解析位置即认为空间需要覆盖，会在存储位置处往下找
 *       新的‘换行行’，新的开始解析位置将会是这个‘换行行’的第一个字符的位置
 *
 *@详情：
 *    1，keyboard_mode与默认模式
 *       keyboard_mode会立即处理换行，适合使用键盘给缓冲区输入，遇到换行会立即在最下面产生空白的新行，而默认模式是不会进行多余的空白显示的
 *       如果缓冲区最后一个是'\n'，keyboard_mode会显示一个空白行，而默认模式不会显示
 *    2，filterOut_char与默认模式
 *       使能filterOut_char会过滤掉字符缓冲区中与filter_buf一样的字符，只过滤显示，不过滤存储
 *    3，scroll_enable
 *       使能scroll_enable会导致NORMAL和AUTO_BREAKLINE解析器窗口输入跟踪，你输入的字符始终在窗口内，不会看不到输入字符。也会导致CONSOLE_PRINT
 *       解析器跟踪最新的log
 *    4，scroll_anim
 *       使能scroll_anim会导致窗口跟踪产生动画（NORMAL，AUTOBREAKLINE）或滚动动画(CONSOLE_PRINT)开启平滑过渡的线性动画，滚动会根据未滚动的行数
 *       线性增加滚动速度，窗口跟踪也是同样道理。三种解析器产生的动画原理不同，前两种依靠窗口跟踪输入位置不同产生动画偏移，CONSOLE_PRINT是根据
 *       txtViewer_printf计算process_cnt什么时候产生新行，继而偏移scroll_pixel，只要有新行就有动画，CONSOLE_PRINT模式设计就是为了命令行输出模式，
 *       使用光标随意输入就违背了它的设计原则，因为光标模式输入不会偏移scroll_pixel产生新行动画，同时导致process_cnt计算混乱，新行就会计算错误，
 *       就会导致动画错乱，因此CONSOLE_PRINT模式下禁止光标输入，只用printf.
 *    5，loop_show
 *       因为在初始化时没有定时更新函数，要想实现初始化打印操作，应改首先不使能该变量
 *    6，scroll_pixel
 *       CONSOLE_PRINT解析器的历史行查看偏移量，scroll_pixel越大，向上滚动的深度越大，查看的历史行越多
 *    7，txt_ofsetX
 *       NORMAL解析器的相对于文本的X偏移量
 *    8，txt_ofsetY
 *       NORMAL和AUTOBREAKLINE解析器的相对于文本的Y偏移量
 *    9，window_x,window_y,window_w,window_h
 *       以次为窗口左上顶点的x坐标，窗口左上顶点的y坐标，窗口宽度，窗口高度
 *    10，char_h，char_w
 *       字体的高度和宽度
 *    11，cursor_enable
 *        光标模式会显示当前光标的位置，存储和删除字符光标位置，需要很大性能
 *
 *@移植依赖：
 *       本程序的最底层只依赖单个字体的高度和宽度，如果想要支持窗口分割，就必须重新实现依赖不同显示屏的的mydraw_bitmap函数，
 *       单色屏幕实现起来较为复杂，因为每个数据bit就是一个像素点，在写数据时需要时刻注意窗口位置，写数据位置，窗口大小的关系
 *       会经常出现窗口边沿分割图像数据的情况，彩色屏幕将会比较简单，因为一个像素点是多个字节，只需要判断像素点的坐标与窗口的关系即可
 *
 *@使用示例：
 *       keypress:
 *           apis();
 *       not loop show to loop show:
 *           txtViewer.loop_show = true;
 *           
 *       SETUP:
 *           txtViewer_init(&txtViewer,buf_size,win_x,win_y,NORMAL);
 *       LOOP:
 *           txtViewer.run(&txtViewer);
 */
 
#include "TXT_Viewer.h"
#include <stdlib.h>
#include "typedef.h"
#include <stdarg.h>
#include "freetype_draw.h"

#define CHAR_HEIGHT         18
#define CHAR_WITH           18

//要过滤的字符,字符过滤是指显示过滤，实际上已经存储在内存里了
static wchar_t * filter_buf = L"\r\t";
//test buf
wchar_t * clang = L"int main(int argc, char **argv)\n{\n\n    printf(\"hello world!\");\n    return 0;\n}\n";

#if SUPPORT_DIFFERENT_CHAR_W

// 字符宽度表，包含所有ASCII字符
int characterWidths[128] = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // ASCII 0-15
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  // ASCII 16-31
// ' ', '!', '"', '#', '$', '%', '&', ''', '(', ')', '*', '+', ',', '-', '.', '/'
    10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  10,  // ASCII 32-47 
// '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ':', ';', '<', '=', '>', '?'
    10,  10,  10,  10,  11,  10,  10,  9,   10,  10,  10,  10,  10,  10,  10,  10,  // ASCII 48-63 (数字和符号)
// '@', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O'
    10,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  // ASCII 64-79
// 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '[', '\', ']', '^', '_'
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  // ASCII 80-95
// '`', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o'
    10,  10,  10,  10,  9,   9,   11,  10,  4,   7,   10,  9,   12,  10,  11,  10,  // ASCII 96-111 (小写字母和符号)
// 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '{', '|', '}', '~', 'DEL'
    9,   10,  10,  10,  10,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0  // ASCII 112-127
};

// 用于判断是否是ASCII字符
bool isASCII(wchar_t c) {
    return (c >= 0x00 && c <= 0x7F);
}

// 获取字符宽度的函数
int getCharWidth(txtViewer_t *viewer, wchar_t character) {
#if SUPPORT_TABLE_WIDTH
    int width = 0;
	if (isASCII(character)) {
		if (character >= 32 && character <= 127) {
        	width = characterWidths[(int)character];
    	}
		 // 如果返回0, 是默认宽度
    	return width == 0 ? viewer->char_w/2 : width;
	} else {
		return viewer->char_w;
	}
   
#else // 认为英文是中文宽度的一半
	if (isASCII(character)) {
		return viewer->char_w/2;
	} else {
		return viewer->char_w;
	}
#endif
}



#endif

millis8_t millis()
{
	static millis8_t ms=0;
	ms++;
	return ms;
}
//字符缓冲区解析器：

//1，普通文本模式，类似txt文本遇到换行符换行
static void txtViewer_display_normal(txtViewer_t *viewer);
//2，文本自动换行模式，在文本模式下增加自动换行功能，
static void txtViewer_display_autoBreakLine(txtViewer_t *viewer);
//3，终端打印模式，显示起始位置是字符缓冲区的最后几行，只要屏幕没有用完，始终有新行动画，支持初始化滚动打印，可以完全替代gui_log_console.c,内存利用率更高
static void txtViewer_console_print(txtViewer_t *viewer);


static u16 getTotalLine_AutoBrk(txtViewer_t *viewer, u8 col_cnt);
static void Recalculate_processed_cnt(txtViewer_t *viewer);
static void Recalculate_processed_pixel(txtViewer_t *viewer);
static void txtViewer_printf(txtViewer_t *viewer, wchar_t *fmt, ...);
static void txtViewer_run(txtViewer_t *viewer);
//包装画图库
static void txtViewer_drawOneChar(wchar_t* string, bool invert, s16 x, s16 y, s16 win_start_x, s16 win_start_y, s16 win_end_x, s16 win_end_y)
{
    // wchar_t c = *string - 0x20;
    // mydraw_bitmap(x, y, smallFont[(byte)c], SMALLFONT_WIDTH, SMALLFONT_HEIGHT, invert, 0,start_x, start_y, boundary_h,boundary_w);
	freetype_draw_one_char_cache(&string[0],0xFFFFFF, x, y, win_start_x, win_start_y, win_end_x, win_end_y);
}

static void txtViewer_printOneChar(s16 x, s16 y, wchar_t *str, s16 win_start_x, s16 win_start_y, s16 win_end_x, s16 win_end_y)
{
	txtViewer_drawOneChar(str, false, x, y, win_start_x, win_start_y, win_end_x, win_end_y);
}
//光标
// const byte Curosor_str[][7] = {{0xFF,0x00,0x00,0x00,0x00,0x00,0x00}};
static void txtViewer_printCursor(s16 x, s16 y, s16 start_x, s16 start_y, s16 boundary_h, s16 boundary_w)
{
	wchar_t cursor_str= L'_';
	// mydraw_bitmap(x, y, Curosor_str[0], 7, SMALLFONT_HEIGHT, 0, 0,start_x, start_y, boundary_h,boundary_w);
	freetype_draw_one_char_cache(&cursor_str, 0xFFFFFF, x, y, start_x, start_y, boundary_h, boundary_w);
}

//静态字符缓冲区，由于使用malloc分配太大内存成功率不高，改为静态分配
static wchar_t buf[1024]={L'A'};

//为TXT_VIewer初始化，为其分配缓存
void txtViewer_init(txtViewer_t *viewer, int size, s16 win_x, s16 win_y, p_mode_t p_mode)
{
	viewer->char_h =  CHAR_HEIGHT;
	viewer->char_w =  CHAR_WITH;
	viewer->buf_size = size;
	viewer->txt_ofsetX = 0;
	viewer->txt_ofsetY = 0;
	viewer->window_x = win_x;
	viewer->window_y = win_y;
	viewer->window_h = 172;
	viewer->window_w = 320;
	viewer->data_buf = buf;
	viewer->printf = txtViewer_printf;
	//console_log(1,"malloc");
	//if(viewer->data_buf == NULL)
		//console_log(1,"malloc err!");
	//else
		//console_log(1,"success");
	// console_log(1,"open Viewer!");
	
	viewer->disp_cb.start_charIdx = 0;
	viewer->disp_cb.store_charIdx = 0;
	viewer->disp_cb.cursor_idx = viewer->disp_cb.store_charIdx;
	viewer->loop_show = true;//始终循环解析
	viewer->scroll_anim = true;//开启动画
	viewer->scroll_enable = false;//禁止窗口跟踪（NORMAL，AUTOBREAKLINE）或滚动(CONSOLE_PRINT)
	viewer->keyboard_mode = true;//关闭键盘输入
	viewer->filterOut_char = true;//滤除'\r'字符
	viewer->cursor_enable = true;//打开光标
	viewer->process_mode = p_mode;
	viewer->input_updata = false;//输入更新
	viewer->win_boundary = false;//绘制窗口
	viewer->cmd_mode = false;
	viewer->run = txtViewer_run;
	switch(p_mode)
	{
		case NORMAL: viewer->process = txtViewer_display_normal;break;
		case AUTO_BREAKLINE: viewer->process = txtViewer_display_autoBreakLine;break;
		case CONSOLE_PRINT: viewer->process = txtViewer_console_print;break;
		default:break;
	}
	// txtViewer_printf(viewer,L"0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n");
	// txtViewer_printf(viewer,L"0\n1\n2\n3\n");
	txtViewer_printf(viewer,L"he\rllo,th\ris is a test.\ncan you see something here?\nIf you can see some words\nThis test may have succeeded!\n");
	txtViewer_printf(viewer,clang);
	// txtViewer_printf(viewer,L"你好，你能看到这些文字？如果可以清晰的看到，说明这个测试成功了！\n");
	viewer->scroll_enable = false;
}

//输入一个字符
void txtViewer_getChar(txtViewer_t *viewer,wchar_t data)
{
	if(!viewer->input_updata) {
		viewer->getchar = data;
		viewer->input_updata = true;
	}
}
//更换解析器
void txtViewer_changeProcessMode(txtViewer_t *viewer, p_mode_t p_mode)
{
	switch(p_mode)
	{
		case NORMAL: viewer->process = txtViewer_display_normal;break;
		case AUTO_BREAKLINE: viewer->process = txtViewer_display_autoBreakLine;break;
		case CONSOLE_PRINT: viewer->process = txtViewer_console_print;break;
		default:break;
	}
	viewer->process_mode = p_mode;
	viewer->txt_ofsetX = 0;
	viewer->txt_ofsetY = 0;
	viewer->scroll_enable = false;
	viewer->disp_cb.cursor_idx = viewer->disp_cb.store_charIdx;
	Recalculate_processed_cnt(viewer);
	#if SUPPORT_DIFFERENT_CHAR_W
	Recalculate_processed_pixel(viewer);
	#endif
}

void txtViewer_clearDataBuf(txtViewer_t *viewer)
{
	viewer->disp_cb.start_charIdx = 0;
	viewer->disp_cb.store_charIdx = 0;
	viewer->data_buf[viewer->disp_cb.store_charIdx]=L'\0';
	viewer->txt_ofsetX = 0;
	viewer->txt_ofsetY = 0;
	viewer->disp_cb.cursor_idx = 0;
	
	Recalculate_processed_cnt(viewer);
	#if SUPPORT_DIFFERENT_CHAR_W
	Recalculate_processed_pixel(viewer);
	#endif
}

static u8 is_filterChar(wchar_t chr, wchar_t *filter_buf)
{
	while(*filter_buf != L'\0')
	{
		if(chr == *filter_buf++)
			return true;
	}
	return false;
}

void setFilterOut(txtViewer_t *viewer)
{
	viewer->filterOut_char = !viewer->filterOut_char;
	Recalculate_processed_cnt(viewer);
	#if SUPPORT_DIFFERENT_CHAR_W
	Recalculate_processed_pixel(viewer);
	#endif
}

//更换解析字符源
void txtViewer_changeSource(txtViewer_t *viewer, txtViewer_t *new_source)
{
	if(new_source->data_buf == NULL||new_source->data_buf == viewer->data_buf )
		return;
	viewer->disp_cb.start_charIdx = new_source->disp_cb.start_charIdx;
	viewer->disp_cb.store_charIdx = new_source->disp_cb.store_charIdx;
	viewer->data_buf = new_source->data_buf;
}

//获取循环缓冲区的这个字符的下一个字符位置
static int getNext(txtViewer_t *viewer, u16 last_char_idx)
{
    last_char_idx++;
    if(last_char_idx >= viewer->buf_size)
    {
        last_char_idx = 0;
    }
    return last_char_idx;
}
static int getLast(txtViewer_t *viewer, u16 last_char_idx)
{
    last_char_idx--;
    if(last_char_idx >= viewer->buf_size)
    {
        last_char_idx = viewer->buf_size-1;
    }
    return last_char_idx;
}


static u16 findNewStartIdx(txtViewer_t *viewer)
{
	u16 store_idx = getNext(viewer,viewer->disp_cb.store_charIdx);
	
	while( viewer->data_buf[store_idx] != L'\n'
		&& store_idx != viewer->disp_cb.store_charIdx )
	{
		store_idx = getNext(viewer,store_idx);
	}
	
	if(store_idx == viewer->disp_cb.store_charIdx)
		return store_idx;
	else
		return getNext(viewer,store_idx);
	
}


//切换窗口需要重新计算viewer->processd_cnt
static void Recalculate_processed_cnt(txtViewer_t *viewer)
{
	u16 cnt = 0;
	if(viewer->disp_cb.store_charIdx == viewer->disp_cb.start_charIdx) {
		viewer->processd_cnt = 0;
		return;
	}
	//除去结束符
	u16 idx = getLast(viewer,viewer->disp_cb.store_charIdx);
	u16 col_cnt = viewer->window_w/viewer->char_w;
	cnt = 0;
	while( viewer->data_buf[idx] != L'\n'
		&& idx != viewer->disp_cb.start_charIdx )
	{
		
		//过滤字符
		if(viewer->filterOut_char) {
			if(!is_filterChar(viewer->data_buf[idx],filter_buf))
				cnt++;
		}
		else {
			cnt++;
		}
		
		idx = getLast(viewer,idx);
	}
	//这种情况会少算一个，需要特殊处理一下
	if(idx == viewer->disp_cb.start_charIdx) {
		if(viewer->filterOut_char) {
			if(!is_filterChar(viewer->data_buf[idx],filter_buf))
				cnt++;
		}
		else {
			cnt++;
		}
	}
	if(viewer->process_mode != NORMAL)
		viewer->processd_cnt = cnt % col_cnt;
	else
		viewer->processd_cnt = cnt;
}
//设置窗口大小
void txtViewer_setWindow(txtViewer_t *viewer, s16 h, s16 w )
{
	viewer->window_h = h;
	viewer->window_w = w;
	viewer->txt_ofsetX = 0;
	viewer->txt_ofsetY = 0;
	Recalculate_processed_cnt(viewer);
	#if SUPPORT_DIFFERENT_CHAR_W
	Recalculate_processed_pixel(viewer);
	#endif
}

//从第line行开始，根据剩余的行数成比例增加动画速度
static int txtViewer_Dynamic_Aim_Speed(txtViewer_t *viewer)
{
	//速度最大为 (字符高度viewer->char_h-line+1) Pixels
	// if (line > viewer->char_h)
	// 	return 0;
	// return viewer->scroll_pixel<=line*viewer->char_h ? 3:(viewer->char_h/8)+txtViewer_Dynamic_Aim_Speed(viewer, line+1);
	#define DEFAULT_SPEED  2
	int delt_speed = 0;
	if(abs(viewer->scroll_pixel) > DEFAULT_SPEED)
		delt_speed = viewer->scroll_pixel / viewer->char_h;
	else
		return 0;
	// 加上基础速度
	return viewer->scroll_pixel >= 0 ? delt_speed + DEFAULT_SPEED : delt_speed - DEFAULT_SPEED;
}
//从第line行开始，根据剩余的行数成比例增加动画速度
static u8 Dynamic_Aim_SpeedForWindow(txtViewer_t *viewer,u8 start_step, u8 step_size, s16 depend)
{
	// u8 max_speed = 16;//pixel
	// //速度最大为 (max_speed-line+1) Pixels
	// if (start_step > max_speed)
	// 	return 0;
	// return depend<=start_step*step_size ? 2:1+Dynamic_Aim_SpeedForWindow(viewer, start_step+1, step_size, depend);

	u8 set_speed = depend / step_size;
	// 加上基础速度
	return set_speed + 3;
}
//删除最后一个存储位置的字符，当然取决于是否过滤的字符
void txtViewer_DeleteLastStoreChar(txtViewer_t *viewer)
{
	if(viewer->disp_cb.store_charIdx == viewer->disp_cb.start_charIdx)
		return;
	//除去结束符
	u16 char_idx = getLast(viewer,viewer->disp_cb.store_charIdx);
	
	//跳到非滤除字符的位置
	if(viewer->filterOut_char)
	{
		while(is_filterChar(viewer->data_buf[char_idx], filter_buf))
		{
			if(char_idx == viewer->disp_cb.start_charIdx)
			{
				return;
			}

			char_idx = getLast(viewer, char_idx);
		}
	}

#if SUPPORT_DIFFERENT_CHAR_W
	do {
		// 重新计算processd_pixel
		int delt_w = getCharWidth(viewer, viewer->data_buf[char_idx]);
		if (viewer->processd_pixel == 0) {
			viewer->processd_pixel = viewer->window_w - delt_w;
		} else {
			viewer->processd_pixel -= delt_w;
		}
	} while(0);
#else
	do {
		// 重新计算processd_cnt
		if (viewer->processd_cnt == 0) {
			viewer->processd_cnt = viewer->window_w/viewer->char_w -1;
		} else {
			viewer->processd_cnt--;
		}
	} while(0);
	
#endif

	viewer->disp_cb.store_charIdx = char_idx;
	viewer->data_buf[viewer->disp_cb.store_charIdx]=L'\0';
	//定位光标
	viewer->disp_cb.cursor_idx = viewer->disp_cb.store_charIdx;
}

//光标指向位置删除字符
void txtViewer_CursorDeleteChar(txtViewer_t *viewer)
{
	if(!viewer->cursor_enable)
		return;
	if(viewer->process_mode == CONSOLE_PRINT)
		return;
	if(viewer->disp_cb.cursor_idx == viewer->disp_cb.start_charIdx)
		return;
	viewer->scroll_enable = true;
	u8 flag=0;
	u16 j,i = viewer->disp_cb.cursor_idx;
	//找到要删除的字符
	if(viewer->filterOut_char) {
		//滤除字符
		i = getLast(viewer, i);
		if(i == viewer->disp_cb.start_charIdx)
			flag=1;
		while(is_filterChar(viewer->data_buf[i], filter_buf)) {
			if(flag)
				return;
			i = getLast(viewer, i);
			if(i == viewer->disp_cb.start_charIdx)
				flag=1;
		}
		
	} else {
		i = getLast(viewer, i);
	}
	j=i;
	//字节移动
	for(;j != viewer->disp_cb.store_charIdx; i = getNext(viewer,i))
	{
		j = getNext(viewer,i);
		viewer->data_buf[i] = viewer->data_buf[j];
	}
	viewer->disp_cb.store_charIdx = getLast(viewer, viewer->disp_cb.store_charIdx);
	viewer->disp_cb.cursor_idx = getLast(viewer, viewer->disp_cb.cursor_idx);
}

//光标指向位置增加字符
void txtViewer_CursorAddChar(txtViewer_t *viewer, wchar_t data)
{
	if(!viewer->cursor_enable)
		return;
	if(viewer->process_mode == CONSOLE_PRINT)
		return;
	viewer->scroll_enable = true;
	//如果内存满了，最后的字符被新增加的字符覆盖
	if(getNext(viewer,viewer->disp_cb.store_charIdx) != viewer->disp_cb.start_charIdx) {
		viewer->disp_cb.store_charIdx = getNext(viewer,viewer->disp_cb.store_charIdx);
		viewer->data_buf[viewer->disp_cb.store_charIdx] = L'\0';
	}
	else
	{
		//如果写满，且光标在最后一个位置，就不写了
		if(viewer->disp_cb.cursor_idx == viewer->disp_cb.store_charIdx)
		{
			return;
		}
	}
	
	u16 i,j = getLast(viewer,viewer->disp_cb.store_charIdx);
	i=j;
	//字节移动
	for(;i != viewer->disp_cb.cursor_idx; j = getLast(viewer,j))
	{
		i = getLast(viewer,j);
		viewer->data_buf[j] = viewer->data_buf[i];
	}
	//写入增加的字符
	viewer->data_buf[viewer->disp_cb.cursor_idx] = data;
	viewer->disp_cb.cursor_idx = getNext(viewer, viewer->disp_cb.cursor_idx);
}


static u16 calculat_CursorCharcnt(txtViewer_t *viewer)
{
	u16 cnt=0;
	u16 col_cnt = viewer->window_w/viewer->char_w;
	u16 cursor_idx = viewer->disp_cb.cursor_idx;
	//这种情况说明是空
	if(cursor_idx == viewer->disp_cb.start_charIdx)
		return cnt;
	//不统计光标位置
	cursor_idx = getLast(viewer,cursor_idx);
	if(cursor_idx == viewer->disp_cb.start_charIdx) {
		return cnt;
	}
	while( viewer->data_buf[cursor_idx] != L'\n' ) {
		//过滤字符
		if(viewer->filterOut_char) {
			if(!is_filterChar(viewer->data_buf[cursor_idx],filter_buf))
				cnt++;
		}
		else {
			cnt++;
		}
		cursor_idx = getLast(viewer,cursor_idx);
		if(cursor_idx == viewer->disp_cb.start_charIdx) {
			break;
		}
	}
	////这种情况说明buf非空，就要统计最后一个了
	if(cursor_idx == viewer->disp_cb.start_charIdx) {
		if(viewer->filterOut_char) {
			if(!is_filterChar(viewer->data_buf[cursor_idx],filter_buf))
				cnt++;
		}
		else {
			cnt++;
		}
	}
	if(viewer->process_mode != NORMAL)
		return (cnt) % col_cnt;
	else
		return cnt;
}


//光标向上
void cursor_up(txtViewer_t *viewer)
{
	if(!viewer->cursor_enable)
		return;
	viewer->scroll_enable = true;
	u16 cursor_idx = viewer->disp_cb.cursor_idx;
	//已经是最前面
	if(cursor_idx == viewer->disp_cb.start_charIdx)
		return;
	
	if (viewer->process_mode == NORMAL) {
		u16 thisline_cnt = calculat_CursorCharcnt(viewer)+1;
		if(viewer->data_buf[cursor_idx] == '\n') {
			cursor_idx = getLast(viewer,cursor_idx);
			if(cursor_idx == viewer->disp_cb.start_charIdx) {
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
		}
			
		//向前找第一个换行
		while( viewer->data_buf[cursor_idx] != '\n' ) {
			cursor_idx = getLast(viewer,cursor_idx);
			if(cursor_idx == viewer->disp_cb.start_charIdx) {
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
		}
		//跳过这个换行
		cursor_idx = getLast(viewer,cursor_idx);
		if(cursor_idx == viewer->disp_cb.start_charIdx)
		{
			viewer->disp_cb.cursor_idx = cursor_idx;
			return;
		}
		//向前找第二个换行
		while( viewer->data_buf[cursor_idx] != '\n' ) {
			cursor_idx = getLast(viewer,cursor_idx);
			if(cursor_idx == viewer->disp_cb.start_charIdx) {
				break;
			}
		}
		
		//在这一行移动光标
		while(thisline_cnt) {
			if(viewer->filterOut_char) {
				if(!is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) 
					thisline_cnt--;
				cursor_idx = getNext(viewer, cursor_idx);
			} else {
				cursor_idx = getNext(viewer, cursor_idx);
				thisline_cnt--;
			}
			if(cursor_idx == viewer->disp_cb.store_charIdx)
			{
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
			if(viewer->data_buf[cursor_idx] == '\n')
			{
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
		}
		viewer->disp_cb.cursor_idx = cursor_idx;
	} else if (viewer->process_mode == AUTO_BREAKLINE) {
			u16 col_cnt = viewer->window_w/viewer->char_w;
			u16 cnt = calculat_CursorCharcnt(viewer);
			
		
			if(viewer->data_buf[cursor_idx] == '\n') {
				cursor_idx = getLast(viewer,cursor_idx);
				if(cursor_idx == viewer->disp_cb.start_charIdx) {
					viewer->disp_cb.cursor_idx = cursor_idx;
					return;
				}
			}

			//尝试直接,viewer->data_buf[cursor_idx] != '\n'还是换行就跳过
			while(col_cnt && viewer->data_buf[cursor_idx] != '\n') {
				
				if(viewer->filterOut_char) {
					if(!is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) 
						col_cnt--;
					cursor_idx = getLast(viewer, cursor_idx);
				} else {
					cursor_idx = getLast(viewer, cursor_idx);
					col_cnt--;
				}
				if(cursor_idx == viewer->disp_cb.start_charIdx)
				{
					viewer->disp_cb.cursor_idx = cursor_idx;
					return;
				}
				
			}
			if(viewer->data_buf[cursor_idx] == '\n')
			{
				viewer->disp_cb.cursor_idx = cursor_idx;
			}
			if(col_cnt == 0 ) {
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
			
			u16 upline_cnt = calculat_CursorCharcnt(viewer);

			if(upline_cnt<cnt)
				upline_cnt=cnt;
			//在上一行移动光标
			while(upline_cnt - cnt) {
				if(viewer->filterOut_char) {
					if(!is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) 
						upline_cnt--;
					cursor_idx = getLast(viewer, cursor_idx);
				} else {
					cursor_idx = getLast(viewer, cursor_idx);
					upline_cnt--;
				}
				if(cursor_idx == viewer->disp_cb.start_charIdx)
				{
					viewer->disp_cb.cursor_idx = cursor_idx;
					return;
				}

			}
			viewer->disp_cb.cursor_idx = cursor_idx;	
		
	}
}


//光标向下(完全无bug)
void cursor_down(txtViewer_t *viewer)
{
	if(!viewer->cursor_enable)
		return;
	viewer->scroll_enable = true;
	u16 cursor_idx = viewer->disp_cb.cursor_idx;
	//已经是最后面
	if(cursor_idx == viewer->disp_cb.store_charIdx)
		return;
	/////
	if (viewer->process_mode == NORMAL) {
		//统计这一行的字符数
		u16 cnt = calculat_CursorCharcnt(viewer);

		while( viewer->data_buf[cursor_idx] != L'\n' ) {
			cursor_idx = getNext(viewer,cursor_idx);
			if(cursor_idx == viewer->disp_cb.store_charIdx) {
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
		}
		//跳过这个换行
		cursor_idx = getNext(viewer,cursor_idx);
		if(cursor_idx == viewer->disp_cb.store_charIdx)
		{
			viewer->disp_cb.cursor_idx = cursor_idx;
			return;
		}
		//在下一行移动光标
		while(cnt) {
			if(viewer->filterOut_char) {
				if(!is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) 
					cnt--;
				cursor_idx = getNext(viewer, cursor_idx);
			} else {
				cursor_idx = getNext(viewer, cursor_idx);
				cnt--;
			}
			if(cursor_idx == viewer->disp_cb.store_charIdx)
			{
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
			if(viewer->data_buf[cursor_idx] == L'\n')
			{
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
		}
		viewer->disp_cb.cursor_idx = cursor_idx;
		
		
	} else if (viewer->process_mode == AUTO_BREAKLINE) {
			u16 col_cnt = viewer->window_w/viewer->char_w;
			u16 cnt = calculat_CursorCharcnt(viewer);

			//尝试直接，光标处是换行就跳过
			while(col_cnt && viewer->data_buf[cursor_idx] != L'\n') {
				
				if(viewer->filterOut_char) {
					if(!is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) 
						col_cnt--;
					cursor_idx = getNext(viewer, cursor_idx);
				} else {
					cursor_idx = getNext(viewer, cursor_idx);
					col_cnt--;
				}
				if(cursor_idx == viewer->disp_cb.store_charIdx)
				{
					viewer->disp_cb.cursor_idx = cursor_idx;
					return;
				}
			}
			if(col_cnt == 0) {
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
			//跳过这个换行
			cursor_idx = getNext(viewer,cursor_idx);
			if(cursor_idx == viewer->disp_cb.store_charIdx)
			{
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
			//在下一行移动光标
			while(cnt && viewer->data_buf[cursor_idx] != L'\n') {
				if(viewer->filterOut_char) {
					if(!is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) 
						cnt--;
					cursor_idx = getNext(viewer, cursor_idx);
				} else {
					cursor_idx = getNext(viewer, cursor_idx);
					cnt--;
				}
				if(cursor_idx == viewer->disp_cb.store_charIdx)
				{
					viewer->disp_cb.cursor_idx = cursor_idx;
					return;
				}
				if(viewer->data_buf[cursor_idx] == L'\n')
				{
					viewer->disp_cb.cursor_idx = cursor_idx;
					return;
				}
			}
			viewer->disp_cb.cursor_idx = cursor_idx;
			
	}
}
//光标--
void cursor_left(txtViewer_t *viewer)
{
	if(!viewer->cursor_enable)
		return;
	viewer->scroll_enable = true;
	if(viewer->process_mode == CONSOLE_PRINT)
		return;
	if(viewer->disp_cb.cursor_idx == viewer->disp_cb.start_charIdx)
		return;
	u16 cursor_idx = viewer->disp_cb.cursor_idx;
	cursor_idx = getLast(viewer, cursor_idx);
	if(cursor_idx == viewer->disp_cb.start_charIdx) {
		viewer->disp_cb.cursor_idx = cursor_idx;
		return;
	}
	if(viewer->filterOut_char) {
		//滤除字符
		while(is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) {
			cursor_idx = getLast(viewer, cursor_idx);	
			if(cursor_idx == viewer->disp_cb.start_charIdx) {
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
		}
		
	}
	viewer->disp_cb.cursor_idx = cursor_idx;
}
//光标++
void cursor_right(txtViewer_t *viewer)
{
	if(!viewer->cursor_enable)
		return;
	viewer->scroll_enable = true;
	if(viewer->process_mode == CONSOLE_PRINT)
		return;
	if(viewer->disp_cb.cursor_idx == viewer->disp_cb.store_charIdx)
		return;
	u16 cursor_idx = viewer->disp_cb.cursor_idx;
	
	cursor_idx = getNext(viewer, cursor_idx);	
	if(cursor_idx == viewer->disp_cb.store_charIdx) {
		viewer->disp_cb.cursor_idx = cursor_idx;
		return;
	}
	if(viewer->filterOut_char) {
		//滤除字符
		while(is_filterChar(viewer->data_buf[cursor_idx], filter_buf)) {
			cursor_idx = getNext(viewer, cursor_idx);	
			if(cursor_idx == viewer->disp_cb.store_charIdx) {
				viewer->disp_cb.cursor_idx = cursor_idx;
				return;
			}
		}
	}
	viewer->disp_cb.cursor_idx = cursor_idx;
}

static void txtViewer_addString(txtViewer_t *viewer, wchar_t *str)
{
	//记录最后一个储存字符是不是换行，如果是下是打印就要加入动画
	static u8 ln_flag = 0;
	u8 flag = 0;
	u16 col_cnt = viewer->window_w/viewer->char_w;
	while(*str != L'\0') {

// 传统打印记录字符的个数, 下面的函数计算process主要有两个目的
// 1，用于定位窗口位置process_cnt是一个代表最后一行的字符个数的变量，可以知道当前的输入位置在什么地方
// 2，用于产生CONSOLE_PRINT新行动画，通过计算process_cnt变量什么时侯大于窗口宽度，可以知道新行在什么时侯产生，并形成动画偏移
// 3，现在要做的事情是通过什么手段代替这两个功能
#if !SUPPORT_DIFFERENT_CHAR_W
		//形成动画偏移
		if(viewer->process_mode == CONSOLE_PRINT ) {
			if(*str == L'\n') {
				if(viewer->keyboard_mode) {
					viewer->scroll_pixel += viewer->char_h;
				} else {
					//多个换行叠加形成偏移
					if(ln_flag) {
						viewer->scroll_pixel += viewer->char_h;
					}
					ln_flag = 1;
				}
				viewer->processd_cnt=0;

			} else {

				//过滤字符
				if(viewer->filterOut_char) {
					if(!is_filterChar(*str,filter_buf)) {
						//'\n'延后换行
						if(ln_flag) {
							viewer->scroll_pixel += viewer->char_h;
						}
						ln_flag = 0;
						viewer->processd_cnt++;
					}
				} else {
					//'\n'延后换行
					if(ln_flag)
						viewer->scroll_pixel += viewer->char_h;
					ln_flag = 0;
					viewer->processd_cnt++;
				}
				
			}

			if(viewer->processd_cnt > col_cnt) {
				viewer->scroll_pixel += viewer->char_h;
				viewer->processd_cnt = 1;
			}
			
		} else if(viewer->process_mode == NORMAL ) {
			if(*str == L'\n') {
				ln_flag = 1;
				if(viewer->keyboard_mode)
					viewer->processd_cnt=0;
			} else {
				
				//过滤字符
				if(viewer->filterOut_char) {
					
					if(!is_filterChar(*str,filter_buf)) {
						//延后清零
						if(ln_flag)
							viewer->processd_cnt=0;
						ln_flag = 0;
						viewer->processd_cnt++;
					}
					
				} else {
					if(ln_flag)
							viewer->processd_cnt=0;
						ln_flag = 0;
					viewer->processd_cnt++;
				}
			}

			
		} else if(viewer->process_mode == AUTO_BREAKLINE ) {
			if(*str == L'\n') {
				viewer->processd_cnt=0;
			} else {
				
				//过滤字符
				if(viewer->filterOut_char) {
					if(!is_filterChar(*str,filter_buf))
						viewer->processd_cnt++;
				} else {
					viewer->processd_cnt++;
				}
			}

			if(viewer->processd_cnt > col_cnt) {
				viewer->processd_cnt = 1;
			}
			
		}
#endif

// 通过计算最后一行的像素值，来计算新航动画的产生
#if SUPPORT_DIFFERENT_CHAR_W
		if(*str == L'\n') {
			viewer->processd_pixel=0;
			viewer->scroll_pixel += viewer->char_h;
		} else {
			int ok = 0;
			//过滤字符
			if(viewer->filterOut_char) {
				if(!is_filterChar(*str,filter_buf)) {
					ok = 1;
				}
			} else {
				ok =1;
			}
			if (ok) {
				int delt_w = getCharWidth(viewer, *str);
				if (viewer->keyboard_mode) {
					if(viewer->processd_pixel + delt_w == viewer->window_w) {
						viewer->processd_pixel = 0;
						viewer->scroll_pixel += viewer->char_h;
					} else if (viewer->processd_pixel + delt_w > viewer->window_w) {
						viewer->processd_pixel = delt_w;
						viewer->scroll_pixel += viewer->char_h;
					} else {
						viewer->processd_pixel += delt_w;
					}
				} else {
					if (viewer->processd_pixel + delt_w > viewer->window_w) {
						viewer->processd_pixel = delt_w;
						viewer->scroll_pixel += viewer->char_h;
					} else {
						viewer->processd_pixel += delt_w;
					}
				}
			}
		
		}

#endif
		
		viewer->data_buf[viewer->disp_cb.store_charIdx] = *str++;
		viewer->disp_cb.store_charIdx = getNext(viewer,viewer->disp_cb.store_charIdx);
		//需要重新找到开始数据的地址
		if(viewer->disp_cb.store_charIdx == viewer->disp_cb.start_charIdx)
			flag = 1;
	}
	viewer->data_buf[viewer->disp_cb.store_charIdx] = L'\0';
	//循环缓冲区的存储索引开始覆盖显示索引，取第二行第一个字符位置作为新的disp_cb.start_charIdx
	if(flag) {
		viewer->disp_cb.start_charIdx = findNewStartIdx(viewer);
		//找到新行后需要重新计算processed_cnt
		Recalculate_processed_cnt(viewer);
		#if SUPPORT_DIFFERENT_CHAR_W
		Recalculate_processed_pixel(viewer);
		#endif
	}
	//定位光标
	viewer->disp_cb.cursor_idx = viewer->disp_cb.store_charIdx;
}

static wchar_t firststr_buff[1024];
//在结尾处打印字符串
static void txtViewer_printf(txtViewer_t *viewer, wchar_t *fmt, ...)
{
	va_list ap;
	va_start(ap,fmt);
	vswprintf(firststr_buff,1024,fmt,ap);
	va_end(ap);
	txtViewer_addString(viewer, firststr_buff);
	viewer->scroll_enable = true;//打开滚动更新或者窗口跟踪字符位置
	//非循环模式下全速打印，希望以后能规范执行速度
	if(viewer->process_mode == CONSOLE_PRINT && !viewer->loop_show) {
		while(viewer->scroll_pixel) {
			
			// memset(&oledBuffer, 0x00, FRAME_BUFFER_SIZE);
			viewer->process(viewer);
			// oled_flush();
			
		}
	}
}

//NORMAL模式下使用
static u16 getFirstLineIdx(txtViewer_t *viewer,s16 skipCnt)
{
	u16 char_idx;
	char_idx = viewer->disp_cb.start_charIdx;
	
	if(skipCnt <= 0||char_idx == viewer->disp_cb.store_charIdx)
		return viewer->disp_cb.start_charIdx;
	char_idx = getNext(viewer, char_idx);
	
	//循环cnt次,找到要显示的第一行的第一个位置
	while(skipCnt--)
	{
		while( viewer->data_buf[char_idx] != L'\n')
		{
			char_idx = getNext(viewer, char_idx);
		}
		char_idx = getNext(viewer, char_idx);
		if(char_idx == viewer->disp_cb.store_charIdx)
			break;
	}
	return char_idx;
}

//CONSOLE，AURO模式下使用
static u16 getFirstLineIdx_AutoBrk(txtViewer_t *viewer,s16 skipCnt,u8 col_cnt)
{
	u16 char_idx;
	u8 col = 0;
	char_idx = viewer->disp_cb.start_charIdx;
	
	if(skipCnt <= 0||char_idx == viewer->disp_cb.store_charIdx)
		return viewer->disp_cb.start_charIdx;
	
	//循环cnt次,找到要显示的第一行的第一个位置
	while(skipCnt--)
	{
		while( viewer->data_buf[char_idx] != L'\n' && col < col_cnt)
		{
			//过滤字符
			if(viewer->filterOut_char) {
				if(!is_filterChar(viewer->data_buf[char_idx], filter_buf) )
					col++;
			}
			else {
				col++;
			}

			char_idx = getNext(viewer, char_idx);
		}
		col = 0;
		if(viewer->data_buf[char_idx] == L'\n')
			char_idx = getNext(viewer, char_idx);
		if(char_idx == viewer->disp_cb.store_charIdx)
			break;
	}
	return char_idx;
}

//normal模式下使用,同时计算出光标在哪一行
static u16 getTotalLine_noAutoBrk(txtViewer_t *viewer)
{
	u8 line_cnt=0;
	u16 char_idx = viewer->disp_cb.start_charIdx;
	//计算出光标在哪一行
	if(char_idx == viewer->disp_cb.cursor_idx)
		viewer->cursor_lineY = line_cnt;
	//
	while(viewer->data_buf[char_idx] != L'\0')
	{
		while( viewer->data_buf[char_idx] != L'\n' && viewer->data_buf[char_idx] != L'\0')
		{
			char_idx = getNext(viewer, char_idx);
			//计算出光标在哪一行
			if(char_idx == viewer->disp_cb.cursor_idx)
				viewer->cursor_lineY = line_cnt;
		}
		line_cnt++;
		if(viewer->data_buf[char_idx] == L'\n') {
			char_idx = getNext(viewer, char_idx);
			//计算出光标在哪一行
			if(char_idx == viewer->disp_cb.cursor_idx)
				viewer->cursor_lineY = line_cnt;
		}
	}
	//键盘输入模式下如果在末尾检测到有换行，会立即换行操作,增加一行
	if(viewer->keyboard_mode && line_cnt != 0) {
		//除去结束符
		u16 idx = getLast(viewer,viewer->disp_cb.store_charIdx);
		if(viewer->data_buf[idx] == L'\n')
			line_cnt++;
	}
	return line_cnt;
}

//CONSOLE，AURO模式下使用
static u16 getTotalLine_AutoBrk(txtViewer_t *viewer, u8 col_cnt)
{
	u8 line_cnt=0;
	u8 col = 0;
	u16 char_idx = viewer->disp_cb.start_charIdx;
	//计算出光标在哪一行
	if(char_idx == viewer->disp_cb.cursor_idx)
		viewer->cursor_lineY = line_cnt;
	//循环cnt次,找到要显示的第一行的第一个位置
	while(viewer->data_buf[char_idx] != L'\0')
	{
		while( viewer->data_buf[char_idx] != L'\n' && col < col_cnt && viewer->data_buf[char_idx] != L'\0')
		{
			
			//过滤字符
			if(viewer->filterOut_char) {
				if(!is_filterChar(viewer->data_buf[char_idx], filter_buf))
					col++;
			}
			else {
				col++;
			}

			char_idx = getNext(viewer, char_idx);
			//计算出光标在哪一行
			if(char_idx == viewer->disp_cb.cursor_idx)
				viewer->cursor_lineY = line_cnt+col/col_cnt;
		}
		line_cnt++;
		//
		if(viewer->filterOut_char)
		{
			while(is_filterChar(viewer->data_buf[char_idx], filter_buf))
			{
				char_idx = getNext(viewer, char_idx);
				//计算出光标在哪一行
				if(char_idx == viewer->disp_cb.cursor_idx)
					viewer->cursor_lineY = line_cnt;
			}
		}
		col = 0;
		if(viewer->data_buf[char_idx] == L'\n') {
			char_idx = getNext(viewer, char_idx);
			//计算出光标在哪一行
			if(char_idx == viewer->disp_cb.cursor_idx)
				viewer->cursor_lineY = line_cnt;
		}
	}
	//键盘输入模式下如果在末尾检测到有换行，会立即换行操作
	if(viewer->keyboard_mode && line_cnt != 0) {
		//除去结束符
		u16 idx = getLast(viewer,viewer->disp_cb.store_charIdx);
		if(viewer->data_buf[idx] == L'\n')
			line_cnt++;
	}
	return line_cnt;
}

#if SUPPORT_DIFFERENT_CHAR_W
// 重新计算processd_piuxel
static void Recalculate_processed_pixel(txtViewer_t *viewer)
{
	// 获取当前的光标索引值
	u16 delt_w = 0;
	int processed_pixel = 0;
	if(viewer->disp_cb.store_charIdx == viewer->disp_cb.start_charIdx) {
		viewer->processd_pixel = 0;
		return;
	}

	// 去除结束符
	u16 char_idx = getLast(viewer,viewer->disp_cb.store_charIdx);
	
	// 应该先找到开头，然后从最后一行的第一个字符开始向后寻找
	while( viewer->data_buf[char_idx] != L'\n' ) {
		if(char_idx == viewer->disp_cb.start_charIdx) {
			break;
		}
		char_idx = getLast(viewer,char_idx);
	}

	if(viewer->data_buf[char_idx] == L'\n')
		char_idx = getNext(viewer,char_idx);

	// 开始向后寻找
	while(viewer->data_buf[char_idx] != L'\0')
	{
			//过滤字符
			if(viewer->filterOut_char) {
				if(!is_filterChar(viewer->data_buf[char_idx], filter_buf)) {
					delt_w = getCharWidth(viewer,viewer->data_buf[char_idx]);
					processed_pixel += delt_w;
				}
			} else {
				delt_w = getCharWidth(viewer,viewer->data_buf[char_idx]);
				processed_pixel += delt_w;
			}
			
			// 新的一行，等于不算新行
			if (processed_pixel > viewer->window_w) {
				processed_pixel = delt_w;
			}

			char_idx = getNext(viewer, char_idx);
	}

	viewer->processd_pixel = processed_pixel;
}

// 获取该行的光标x坐标像素值
u16 get_cursor_lineX_pixel(txtViewer_t *viewer)
{
	// 获取当前的光标索引值
	u16 delt_w = 0;
	u16 length_x = 0;
	u16 cursor_idx = viewer->disp_cb.cursor_idx;
	//这种情况说明是空
	if(cursor_idx == viewer->disp_cb.start_charIdx)
		return length_x;
	//不统计光标位置
	cursor_idx = getLast(viewer,cursor_idx);
	if(cursor_idx == viewer->disp_cb.start_charIdx) {
		return length_x;
	}
	while( viewer->data_buf[cursor_idx] != L'\n' ) {
		//过滤字符,如果过滤字符就不统计长度
		if(viewer->filterOut_char) {
			if(!is_filterChar(viewer->data_buf[cursor_idx],filter_buf)) {
				delt_w = getCharWidth(viewer, viewer->data_buf[cursor_idx]);
			}
		}
		else {
			delt_w = getCharWidth(viewer, viewer->data_buf[cursor_idx]);
		}
		length_x += delt_w;  // 累加长度
		if(cursor_idx == viewer->disp_cb.start_charIdx) {
			break;
		}
		cursor_idx = getLast(viewer,cursor_idx);
	}

	return length_x;
}

// 根据窗口宽度计算总的行数，为了适应不同字符宽度
static u16 getTotalLine_AutoBrk_DCW(txtViewer_t *viewer)
{
	u16 line_cnt=0;
	u16 thisLine_pixel = 0;
	u16 test_pixel = 0;
	u16 char_idx = viewer->disp_cb.start_charIdx;
	u16 delt_w = 0;
	u8 end_line_full = 0;
	//计算出光标在哪一行
	if(char_idx == viewer->disp_cb.cursor_idx)
		viewer->cursor_lineY = line_cnt;
	//循环cnt次,找到要显示的第一行的第一个位置
	while(viewer->data_buf[char_idx] != L'\0')
	{
		// 计算当前行的结束
		while( viewer->data_buf[char_idx] != L'\n' && viewer->data_buf[char_idx] != L'\0')
		{
			//过滤字符
			if(viewer->filterOut_char) {
				if(!is_filterChar(viewer->data_buf[char_idx], filter_buf)) {
					delt_w = getCharWidth(viewer,viewer->data_buf[char_idx]);
					thisLine_pixel += delt_w;
				}
			} else {
				delt_w = getCharWidth(viewer,viewer->data_buf[char_idx]);
				thisLine_pixel += delt_w;
			}
			
			//计算出光标在哪一行
			if(char_idx == viewer->disp_cb.cursor_idx)
				viewer->cursor_lineY = line_cnt + thisLine_pixel / viewer->window_w;
			
			// 新的一行，等于不算新行
			if (thisLine_pixel > viewer->window_w) {
				break;
			}

			char_idx = getNext(viewer, char_idx);
		}
		line_cnt++;
		// 滤出过滤字符
		if(viewer->filterOut_char)
		{
			while(is_filterChar(viewer->data_buf[char_idx], filter_buf))
			{	
				char_idx = getNext(viewer, char_idx); // 找到有效字符
				//计算出光标在哪一行
				if(char_idx == viewer->disp_cb.cursor_idx)
					viewer->cursor_lineY = line_cnt;
			}
		}

		test_pixel = thisLine_pixel;

		// 判断当前行是否满
		if(thisLine_pixel == viewer->window_w){
			end_line_full = 1;
		} else {
			end_line_full = 0;
		}

		// if (thisLine_pixel > viewer->window_w) 
		{ // 当前行溢出
			thisLine_pixel = 0; // 清零当前行的像素值
		}
		
		// 如果是遇到换行导致新行，就进一步判断，这个换行是不是光标位置
		if(viewer->data_buf[char_idx] == L'\n' || viewer->data_buf[char_idx] == L'\0') { 
			//计算出光标在哪一行
			if(char_idx == viewer->disp_cb.cursor_idx)
				viewer->cursor_lineY = line_cnt;
			char_idx = getNext(viewer, char_idx);
		}
	}

	// wchar_t buffer[10];
	// swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"%d", test_pixel);
	// lcd_draw_character_cache(txtViewer.window_x + txtViewer.window_w,75,buffer,0x0099FF);

	// 防止剩余没有判断
	if(viewer->data_buf[char_idx] == L'\0') { 
		//计算出光标在哪一行
		if(char_idx == viewer->disp_cb.cursor_idx)
			viewer->cursor_lineY = line_cnt;
	}

	// 键盘输入模式下如果在末尾检测到有换行，会立即换行操作
	if(viewer->keyboard_mode && line_cnt != 0 ) {
		//除去结束符
		u16 idx = getLast(viewer,viewer->disp_cb.store_charIdx);
		if(viewer->data_buf[idx] == L'\n') {
			line_cnt++;
		}
		else if(end_line_full) { // 如果当前行满，键盘模式下也进行换行
			line_cnt++;
		}
	}

	return line_cnt;
}

// 获取第一行的索引值，为了适应不同字符宽度
static u16 getFirstLineIdx_AutoBrk_DCW(txtViewer_t *viewer,s16 skipCnt,u8 col_cnt)
{
	u16 char_idx;
	u16 line_cnt=0;
	u16 thisLine_pixel = 0;
	char_idx = viewer->disp_cb.start_charIdx;
	
	if(skipCnt <= 0||char_idx == viewer->disp_cb.store_charIdx)
		return viewer->disp_cb.start_charIdx;
	
	//循环cnt次,找到要显示的第一行的第一个位置
	while(skipCnt--)
	{
		while( viewer->data_buf[char_idx] != L'\n')
		{
			//过滤字符
			if(viewer->filterOut_char) {
				if(!is_filterChar(viewer->data_buf[char_idx], filter_buf)) {
					u16 delt_w = getCharWidth(viewer,viewer->data_buf[char_idx]);
					thisLine_pixel += delt_w;
				}
			} else {
				u16 delt_w = getCharWidth(viewer,viewer->data_buf[char_idx]);
				thisLine_pixel += delt_w;
			}

			// 新的一行
			if (thisLine_pixel > viewer->window_w) {
				break;
			}
			char_idx = getNext(viewer, char_idx);
		}
		thisLine_pixel = 0;  // 清零像素数
		if(viewer->data_buf[char_idx] == L'\n')
			char_idx = getNext(viewer, char_idx);
		if(char_idx == viewer->disp_cb.store_charIdx)
			break;
	}
	return char_idx;
}

#endif  // define SUPPORT_DIFFERENT_CHAR_W

//闪烁光标
void txtViewer_curosrBlink(txtViewer_t *viewer, s16 txt_x, s16 txt_y, u16 char_idx) {
	if(viewer->cursor_enable) {
		static millis8_t lastUpdate;
		millis8_t now = millis();
		if ((millis8_t)(now - lastUpdate) >= 1000)
			lastUpdate = now;
		if ((millis8_t)(now - lastUpdate) < 500) {
			
			if(char_idx == viewer->disp_cb.cursor_idx ) {
				txtViewer_printCursor(txt_x + viewer->window_x, txt_y + viewer->window_y, 
						viewer->window_x,viewer->window_y, viewer->window_y + viewer->window_h, viewer->window_x + viewer->window_w);
			}
		}
	}
}

//普通解析模式
static void txtViewer_display_normal(txtViewer_t *viewer)
{
	//计算需要跳过的行数
	s16 skipLineNum = viewer->txt_ofsetY/viewer->char_h;
	//获取窗口的第一行的第一个字符，比较耗费性能
	u16 char_idx = getFirstLineIdx(viewer,skipLineNum);
	
	//计算窗口每列要显示的字符个数
	u16 line_cnt = viewer->window_h/viewer->char_h+1;
	//计算窗口每行要显示的字符个数
	u16 col_cnt = viewer->window_w/viewer->char_w+1;
	//行打印计数器//列打印计数器
	u16 row_cnt = 0, col_char_cnt = 0;
	
	s16 eachLineCharOffsetNum = viewer->txt_ofsetX/viewer->char_w;
	//计算出所有行和光标的行
	u16 total_line = getTotalLine_noAutoBrk(viewer);
	//计算出光标的列
	viewer->cursor_lineX = calculat_CursorCharcnt(viewer);
	//优先光标跟踪
	if(viewer->cursor_enable && viewer->scroll_enable && viewer->keyboard_mode)
	{
		//x控制
		s16 length_x = (viewer->cursor_lineX+1) * viewer->char_w;
		// 根据cursor_lineX计算出统计新的piex
		// 1.向前统计直到找到换行符号，同时检测英文和中文的宽度
		// 2.计算出新的piex值替换length_x用于后面的窗口位置计算
		// 在这里加上对于length_x的进一步处理的函数
		// 用于处理窗口移动
		#if SUPPORT_DIFFERENT_CHAR_W
		do {
			length_x = get_cursor_lineX_pixel(viewer);
		} while(0);
		#endif
		wchar_t buffer[10];
		swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"%d", length_x);
		lcd_draw_character_cache(txtViewer.window_x + txtViewer.window_w,50,buffer,0x9900FF);

		swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"%d", viewer->processd_pixel);
		lcd_draw_character_cache(txtViewer.window_x + txtViewer.window_w,75,buffer,0x0099FF);

		if(length_x - viewer->txt_ofsetX > viewer->window_w) { 
			if(viewer->scroll_anim)
				viewer->txt_ofsetX+=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_w,length_x - viewer->txt_ofsetX -viewer->window_w);
			else
				viewer->txt_ofsetX=length_x -viewer->window_w;
		}
		if((viewer->cursor_lineX - 5 < 0?0:viewer->cursor_lineX - 5) * viewer->char_w < viewer->txt_ofsetX) {
			if(viewer->scroll_anim)
				viewer->txt_ofsetX-=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_w,viewer->txt_ofsetX - (5* viewer->char_w));
			else
				viewer->txt_ofsetX=((viewer->cursor_lineX - 5)* viewer->char_w) < 0 ? 0:(viewer->cursor_lineX - 5)* viewer->char_w;
		}
		//y控制
		s16 length_y = viewer->char_h * (viewer->cursor_lineY+1);
		if(length_y - viewer->txt_ofsetY > viewer->window_h) { //防止光标在窗口下面
			if(viewer->scroll_anim)
				viewer->txt_ofsetY+=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_h,length_y - viewer->txt_ofsetY - viewer->window_h);
			else
				viewer->txt_ofsetY=length_y - viewer->window_h;
		}
		if(viewer->cursor_lineY * viewer->char_h < viewer->txt_ofsetY) { //防止光标在窗口上面
			if(viewer->scroll_anim)
				viewer->txt_ofsetY-=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_h,viewer->txt_ofsetY - (viewer->cursor_lineY* viewer->char_h));
			else
				viewer->txt_ofsetY=viewer->txt_ofsetY - viewer->char_h;
		}
		length_y = viewer->char_h * total_line;
		//打印时始终保持最后一行在最下面，防止新行改变时整体画面上移，如果有键盘转串口输入，不容易丢失视角
		if(length_y - viewer->txt_ofsetY < viewer->window_h)
			viewer->txt_ofsetY = length_y - viewer->window_h;
	}
	//窗口跟踪字符打印
	else if(viewer->scroll_enable)
	{
		s16 length_x = viewer->processd_cnt * viewer->char_w;
		// 根据processd_cnt计算出统计新的piex
		// 1.向前统计直到找到换行符号，同时检测英文和中文的宽度
		// 2.计算出新的piex值替换length_x用于后面的窗口位置计算
		// 在这里加上对于length_x的进一步处理的函数
		#if SUPPORT_DIFFERENT_CHAR_W
		do {
			length_x = get_cursor_lineX_pixel(viewer);
		} while(0);

		#endif

		if(length_x - viewer->txt_ofsetX > viewer->window_w) { 
			if(viewer->scroll_anim)
				viewer->txt_ofsetX+=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_w,length_x - viewer->txt_ofsetX -viewer->window_w);
			else
				viewer->txt_ofsetX=length_x -viewer->window_w;
		}
		if((viewer->processd_cnt - 5 < 0?0:viewer->processd_cnt - 5) * viewer->char_w < viewer->txt_ofsetX) {
			if(viewer->scroll_anim)
				viewer->txt_ofsetX-=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_w,viewer->txt_ofsetX - (5* viewer->char_w));
			else
				viewer->txt_ofsetX=((viewer->processd_cnt - 5)* viewer->char_w) < 0 ? 0:(viewer->processd_cnt - 5)* viewer->char_w;
		}
		s16 length_y = viewer->char_h * total_line;
		if(length_y - viewer->txt_ofsetY > viewer->window_h) {
			if(viewer->scroll_anim)
				viewer->txt_ofsetY+=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_h,length_y - viewer->txt_ofsetY - viewer->window_h);
			else
				viewer->txt_ofsetY=length_y - viewer->window_h;
		}
		//打印时始终保持最后一行在最下面，防止新行改变时整体画面上移，如果有键盘转串口输入，不容易丢失视角
		if(length_y - viewer->txt_ofsetY < viewer->window_h)
			viewer->txt_ofsetY = length_y - viewer->window_h;
	}
	
	//限制窗口字符行数打印
	while(row_cnt < line_cnt) {
		//解析每一个字符搜索换行，否则符合条件打印出来

			s16 txt_x = (col_char_cnt)*viewer->char_w - viewer->txt_ofsetX;
			s16 txt_y = (row_cnt + (skipLineNum > 0? skipLineNum:0))*viewer->char_h - viewer->txt_ofsetY;

			// 在这里加上对于txt_x的进一步处理的函数
		#if SUPPORT_DIFFERENT_CHAR_W
			do {
				static s16 txt_xx = 0;
				s16 delt_w = 0; 
				
				// 跳过过滤字符的计算
				if(is_filterChar(viewer->data_buf[char_idx], filter_buf) && viewer->filterOut_char) {
					break;
				}
				// 获取字符宽度
				delt_w = getCharWidth(viewer, viewer->data_buf[char_idx]);
				// 该行的第一个字符
				if (col_char_cnt == 0) {
					txt_xx = txt_x + delt_w;
				} else {
					txt_xx += delt_w;
				}
				// 减去此时的字符长度
				txt_x = txt_xx - delt_w;
				
			} while(0);

		#endif
			//打印光标,在停止显示之前
			txtViewer_curosrBlink(viewer, txt_x, txt_y, char_idx);
			
			//当显示到达最新的存储字符位置时停止显示
			if(char_idx ==  viewer->disp_cb.store_charIdx||viewer->data_buf[char_idx] == L'\0')
				break;
			
			//过滤字符
			if(is_filterChar(viewer->data_buf[char_idx], filter_buf) && viewer->filterOut_char) {
				char_idx = getNext(viewer, char_idx);
				continue;
			}
			
			if(viewer->data_buf[char_idx] == L'\n'){
				row_cnt++;
				col_char_cnt = 0;//遇到新的行列打印计数器清零
			}
			else {
			
				#if SUPPORT_DIFFERENT_CHAR_W
				if(txt_x > - viewer->char_w && txt_x < viewer->window_w) {

					txtViewer_printOneChar(txt_x + viewer->window_x, txt_y + viewer->window_y, &viewer->data_buf[char_idx], 
						viewer->window_x,viewer->window_y, viewer->window_y + viewer->window_h, viewer->window_x + viewer->window_w);
				}

				#else
				//限制窗口字符打印de列数
				if(col_char_cnt >= eachLineCharOffsetNum && col_char_cnt < col_cnt + eachLineCharOffsetNum) {
					
					txtViewer_printOneChar(txt_x + viewer->window_x, txt_y + viewer->window_y, &viewer->data_buf[char_idx], 
						viewer->window_x,viewer->window_y, viewer->window_y + viewer->window_h, viewer->window_x + viewer->window_w);
					
				}
				#endif
					
				col_char_cnt++;
			}

			char_idx = getNext(viewer, char_idx);
	}
}

//自动换行解析模式
static void txtViewer_display_autoBreakLine(txtViewer_t *viewer)
{
	//计算窗口每行要显示的字符个数
	u16 col_cnt = viewer->window_w/viewer->char_w;
	//计算需要跳过的行数
	s16 skipLineNum = viewer->txt_ofsetY/viewer->char_h;
	#if SUPPORT_DIFFERENT_CHAR_W
	//获取窗口的第一行的第一个字符比较耗费性能
	u16 char_idx = getFirstLineIdx_AutoBrk_DCW(viewer,skipLineNum,col_cnt);
	#else
	u16 char_idx = getFirstLineIdx_AutoBrk(viewer,skipLineNum,col_cnt);
	#endif
	
	//计算窗口每列要显示的字符个数
	u16 line_cnt = viewer->window_h/viewer->char_h+1;
	
	//行打印计数器//列打印计数器
	u16 row_cnt = 0, col_char_cnt = 0;
	
	#if SUPPORT_DIFFERENT_CHAR_W
	u16 total_line = getTotalLine_AutoBrk_DCW(viewer);
	#else
	u16 total_line = getTotalLine_AutoBrk(viewer,col_cnt);
	#endif

	wchar_t buffer[10];
	swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"%d", total_line);
	lcd_draw_character_cache(txtViewer.window_x + txtViewer.window_w,50,buffer,0x9900FF);

	swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"%d", viewer->processd_pixel);
	lcd_draw_character_cache(txtViewer.window_x + txtViewer.window_w,75,buffer,0x0099FF);

	// wchar_t buffer[10];
	swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"%d", viewer->cursor_lineY);
	lcd_draw_character_cache(txtViewer.window_x + txtViewer.window_w,100,buffer,0x9900FF);
	
	//优先光标跟踪
	if(viewer->cursor_enable&&viewer->scroll_enable && viewer->keyboard_mode)
	{
		//y控制
		s16 length_y = viewer->char_h * (viewer->cursor_lineY+1);
		if(length_y - viewer->txt_ofsetY > viewer->window_h) {
			if(viewer->scroll_anim)
				viewer->txt_ofsetY+=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_h,length_y - viewer->txt_ofsetY - viewer->window_h);
			else
				viewer->txt_ofsetY=length_y - viewer->window_h;
		}
		if(viewer->cursor_lineY * viewer->char_h < viewer->txt_ofsetY) {
			if(viewer->scroll_anim)
				viewer->txt_ofsetY-=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_h,viewer->txt_ofsetY - (viewer->cursor_lineY* viewer->char_h));
			else
				viewer->txt_ofsetY=viewer->txt_ofsetY - viewer->char_h;
		}
		length_y = viewer->char_h * total_line;
		//打印时始终保持最后一行在最下面，防止新行改变时整体画面上移，如果有键盘转串口输入，不容易丢失视角
		if(length_y - viewer->txt_ofsetY < viewer->window_h)
			viewer->txt_ofsetY = length_y - viewer->window_h;
	}
	//窗口跟踪字符打印
	else if(viewer->scroll_enable)
	{
		s16 length_y = viewer->char_h * total_line;
		if(length_y - viewer->txt_ofsetY > viewer->window_h) {
			if(viewer->scroll_anim)
				viewer->txt_ofsetY+=Dynamic_Aim_SpeedForWindow(viewer,1,viewer->char_h,length_y - viewer->txt_ofsetY - viewer->window_h);
			else
				viewer->txt_ofsetY=length_y - viewer->window_h;
		}
		//打印时始终保持最后一行在最下面，防止新行改变时整体画面上移，如果有键盘转串口输入，不容易丢失视角
		if(length_y - viewer->txt_ofsetY < viewer->window_h)
			viewer->txt_ofsetY = length_y - viewer->window_h;
	}
	
	// wchar_t buff[4];
	// sprintf_P(buff, PSTR("%d"), viewer->cursor_lineX);
	// draw_string(buff, NOINVERT, 110, FRAME_HEIGHT - 8);
	// sprintf_P(buff, PSTR("%d"), viewer->cursor_lineY);
	// draw_string(buff, NOINVERT, 110, FRAME_HEIGHT - 16);
	
	//限制窗口字符行数打印
	while(row_cnt < line_cnt) {
		//解析每一个字符搜索换行，否则符合条件打印出来
		static s16 txt_x;
		static s16 txt_y;
		int new_line_flag = 0;

		
			#if !SUPPORT_DIFFERENT_CHAR_W
			//限制窗口字符打印de列数
			if(col_char_cnt >= col_cnt) {
				row_cnt++;
				col_char_cnt = 0;
				new_line_flag = 1;
			}

			txt_x = (col_char_cnt)*viewer->char_w;
			txt_y = (row_cnt + (skipLineNum > 0? skipLineNum:0))*viewer->char_h - viewer->txt_ofsetY;
			#endif
			
			// 在这里加上对于txt_x的进一步处理的函数
			#if SUPPORT_DIFFERENT_CHAR_W
			do {
				static s16 txt_xx = 0;
				s16 delt_w = 0;

				if (col_char_cnt == 0) {
					txt_xx = 0;
				}

				// 获取字符宽度
				delt_w = getCharWidth(viewer, viewer->data_buf[char_idx]);

				// 自动换行,限制窗口字符打印de列数,如果下一个字符的结尾超过
				if (txt_xx + delt_w > viewer->window_w ) {
					row_cnt++;
					new_line_flag = 1;
					col_char_cnt = 0;
					txt_xx = 0;
				} else {
					new_line_flag = 0;
				}

				// txt_x = (col_char_cnt)*viewer->char_w;
				txt_y = (row_cnt + (skipLineNum > 0? skipLineNum:0))*viewer->char_h - viewer->txt_ofsetY;
				
				// 跳过过滤字符的计算
				if(is_filterChar(viewer->data_buf[char_idx], filter_buf) && viewer->filterOut_char) {
					break;
				}

				txt_xx += delt_w;
				
				// 减去此时的字符长度
				txt_x = txt_xx - delt_w;
				
			} while(0);
			#endif

			//打印光标,在显示停止之前
			txtViewer_curosrBlink(viewer, txt_x, txt_y, char_idx);

			//当显示到达最新的存储字符位置时停止显示
			if(char_idx == viewer->disp_cb.store_charIdx || viewer->data_buf[char_idx] == L'\0')
				break;
			
			//过滤字符
			if(is_filterChar(viewer->data_buf[char_idx], filter_buf) && viewer->filterOut_char) {
				char_idx = getNext(viewer, char_idx);
				continue;
			}

			if(viewer->data_buf[char_idx] == L'\n' && !new_line_flag) {
				row_cnt++;
				col_char_cnt = 0;//遇到新的行列打印计数器清零
			} else {

				txtViewer_printOneChar(txt_x + viewer->window_x, txt_y + viewer->window_y, &viewer->data_buf[char_idx], 
							viewer->window_x,viewer->window_y, viewer->window_y + viewer->window_h, viewer->window_x + viewer->window_w);
				
				col_char_cnt++;
			}
			
			char_idx = getNext(viewer, char_idx);
	}
}

// 终端输出解析模式 console print mode
static void txtViewer_console_print(txtViewer_t *viewer)
{
	//计算窗口每行要显示的字符个数
	u16 col_cnt = viewer->window_w/viewer->char_w;
	//计算当前的总行数比较耗费性能
	#if SUPPORT_DIFFERENT_CHAR_W
	u16 total_line = getTotalLine_AutoBrk_DCW(viewer);
	#else
	u16 total_line = getTotalLine_AutoBrk(viewer,col_cnt);
	#endif
	//计算窗口需要显示的行数， 补1
	u16 line_cnt = viewer->window_h/viewer->char_h + 1;
	//历史行最小为一行，因为在形成一行字符瞬间，整体向下偏移一个字符高度，如果不显示一行历史行就会有空洞存在
	u16 history_line = viewer->scroll_pixel/viewer->char_h + 1;
	s16 skipLineNum = total_line - line_cnt + 1 - history_line;

	// 根据跳过的行数计算开始显示的字符位置
	#if SUPPORT_DIFFERENT_CHAR_W
	u16 char_idx = getFirstLineIdx_AutoBrk_DCW(viewer,skipLineNum,col_cnt);
	#else
	u16 char_idx = getFirstLineIdx_AutoBrk(viewer,skipLineNum,col_cnt);
	#endif
	
	//行打印计数器//列打印计数器
	u16 row_cnt = 0, col_char_cnt = 0;
	
	//总行数小于窗口行数，打印不需要滚动的处理，直接打印
	if(total_line  <= line_cnt-1) {
		viewer->scroll_pixel = 0;
		history_line = 0;
		//total_line = 8时skipLineNum=-1，此时不应该偏移，因该直接显示
		skipLineNum = 0;
	}
	
	// 控制动画和显示位置
	if(viewer->scroll_anim) {
		if(SCROLL_AUTO == viewer->scroll_enable) {
			viewer->scroll_pixel -= txtViewer_Dynamic_Aim_Speed(viewer);
			viewer->target_scroll_pixel = viewer->scroll_pixel;
		} else if(SCROLL_MANUAL == viewer->scroll_enable){ // 跟踪 target_scroll_pixel
			int delt = abs(viewer->target_scroll_pixel - viewer->scroll_pixel);
			if (delt > 3)
				viewer->scroll_pixel += viewer->target_scroll_pixel - viewer->scroll_pixel > 0 ? delt/viewer->char_h + 3 : -delt/viewer->char_h -3;
		}
	} else {
		if(viewer->scroll_enable)
			viewer->scroll_pixel = 0;
	}

	//限制最大滚动偏移
	if(viewer->scroll_pixel > 0 && viewer->scroll_pixel > (total_line - line_cnt + 1)*viewer->char_h) {
		viewer->scroll_pixel = (total_line - line_cnt + 1)*viewer->char_h;
		viewer->target_scroll_pixel = viewer->scroll_pixel;
	}
	
	wchar_t buffer[10];
	swprintf(buffer, sizeof(buffer) / sizeof(wchar_t), L"%d", viewer->processd_pixel);
	lcd_draw_character_cache(txtViewer.window_x + txtViewer.window_w,75,buffer,0x0099FF);
	
	//限制窗口字符行数打印
	//显示数等于窗口行高度+2行
	while(row_cnt < line_cnt+1) {
		s16 txt_x;
		s16 txt_y;
		u8 new_line_flag = 0;
		
			#if !SUPPORT_DIFFERENT_CHAR_W
			//限制窗口字符打印de列数
			if(col_char_cnt >= col_cnt) {
				row_cnt++;
				col_char_cnt = 0;
			}
			txt_x = (col_char_cnt)*viewer->char_w;
			//skipLineNum == -1 是一种特殊情况，此时历史行找不到了，变成正常的第一行了，就造成最大偏移时第一行显示的是第二行，负一行显示的是第一行应该弥补
			txt_y = (row_cnt - history_line)*viewer->char_h + viewer->scroll_pixel + (skipLineNum == -1 ? viewer->char_h:0);
			
			#endif
			
			// 在这里加上对于txt_x的进一步处理的函数
			#if SUPPORT_DIFFERENT_CHAR_W
			do {
				static s16 txt_xx = 0;
				s16 delt_w = 0;

				if (col_char_cnt == 0) {
					txt_xx = 0;
				}

				// 获取字符宽度
				delt_w = getCharWidth(viewer, viewer->data_buf[char_idx]);

				// 自动换行,限制窗口字符打印de列数,如果下一个字符的结尾超过
				if (txt_xx + delt_w > viewer->window_w ) {
					row_cnt++;
					new_line_flag = 1;
					col_char_cnt = 0;
					txt_xx = 0;
				} else {
					new_line_flag = 0;
				}

				txt_y = (row_cnt - history_line)*viewer->char_h + viewer->scroll_pixel + (skipLineNum == -1 ? viewer->char_h:0);
				
				// 跳过过滤字符的计算
				if(is_filterChar(viewer->data_buf[char_idx], filter_buf) && viewer->filterOut_char) {
					break;
				}

				txt_xx += delt_w;
				
				// 减去此时的字符长度
				txt_x = txt_xx - delt_w;
				
			} while(0);
			#endif

			//打印光标,在显示停止之前
			txtViewer_curosrBlink(viewer, txt_x, txt_y, char_idx);

			//当显示到达最新的存储字符位置时停止显示
			if(char_idx ==  viewer->disp_cb.store_charIdx || viewer->data_buf[char_idx] == L'\0')
				break;
			
			//过滤字符
			if(is_filterChar(viewer->data_buf[char_idx], filter_buf) && viewer->filterOut_char) {
				char_idx = getNext(viewer, char_idx);
				continue;
			}
			
			//解析每一个字符搜索换行，否则符合条件打印出来
			if(viewer->data_buf[char_idx] == L'\n' && !new_line_flag){
				row_cnt++;
				col_char_cnt = 0;//遇到新的行列打印计数器清零
			}
			else {
				
				txtViewer_printOneChar(txt_x + viewer->window_x, txt_y + viewer->window_y, &viewer->data_buf[char_idx], 
							viewer->window_x,viewer->window_y, viewer->window_y + viewer->window_h, viewer->window_x + viewer->window_w);
				
				col_char_cnt++;
			}
			char_idx = getNext(viewer, char_idx);
			
	}

	// cmd_parser.run(&cmd_parser);
}



void txtViewer_drawBoundary(txtViewer_t *viewer)
{
	// myOLED_DrawLine(viewer->window_x, viewer->window_y, viewer->window_x+viewer->window_w, viewer->window_y,true);
	// myOLED_DrawLine(viewer->window_x+viewer->window_w, viewer->window_y, viewer->window_x+viewer->window_w, viewer->window_y+viewer->window_h,true);
	// myOLED_DrawLine(viewer->window_x, viewer->window_y+viewer->window_h, viewer->window_x+viewer->window_w, viewer->window_y+viewer->window_h,true);
	
	
	// myOLED_DrawLine(viewer->window_x, viewer->window_y, viewer->window_x, viewer->window_y+viewer->window_h,true);
}



#define T_KEY_UP  (1)
#define T_KEY_DOWN (2)
#define T_KEY_LEFT  (3)
#define T_KEY_RIGHT  (4)

static wchar_t * operator_buf = L"\b";
static u8 is_operator(txtViewer_t *viewer)
{
	wchar_t *opt_buf = operator_buf;
	while(*opt_buf != L'\0')
	{
		if(viewer->getchar == *opt_buf++)
			return true;
	}
	if (viewer->getchar == T_KEY_UP || viewer->getchar == T_KEY_DOWN || viewer->getchar == T_KEY_LEFT  || viewer->getchar == T_KEY_RIGHT)
		return true;
	return false;
}

//执行操作符对应的操作
void txtViewer_do_operator(txtViewer_t *viewer)
{
	//退格
	if(viewer->getchar == L'\b') {
		// if (viewer->process_mode == CONSOLE_PRINT) {
		// 	txtViewer_DeleteLastStoreChar(viewer);
		// } else {
			txtViewer_CursorDeleteChar(viewer);
		// }
	} else {
		switch (viewer->getchar) {
			case T_KEY_LEFT: 
			{
				if (viewer->process_mode == CONSOLE_PRINT) {
					txtViewer.scroll_enable = SCROLL_MANUAL;
					txtViewer.target_scroll_pixel -= viewer->char_h;
				} else {
					cursor_left(viewer);
				}
				break;
			}
			case T_KEY_RIGHT:
			{
				if (viewer->process_mode == CONSOLE_PRINT) {
					txtViewer.scroll_enable = SCROLL_MANUAL;
					txtViewer.target_scroll_pixel += viewer->char_h;
				} else {
					cursor_right(viewer);
				}
				break;
			}
			case T_KEY_UP:   
			{
				if (viewer->process_mode == CONSOLE_PRINT) {
					txtViewer.scroll_enable = SCROLL_MANUAL;
					txtViewer.target_scroll_pixel -= viewer->char_h;
				} else {
					 cursor_up(viewer);
				}
				break;
			}
			case T_KEY_DOWN:
			{
				if (viewer->process_mode == CONSOLE_PRINT) {
					txtViewer.scroll_enable = SCROLL_MANUAL;
					txtViewer.target_scroll_pixel += viewer->char_h;
				} else {
					 cursor_down(viewer);
				}
				break;
			}
			default: break;
		}
	}
}

static void txtViewer_run(txtViewer_t *viewer)
{
	if(viewer->input_updata)
	{
		viewer->input_updata = false;
		if(is_operator(viewer)) {
			txtViewer_do_operator(viewer);
		} else {
			//使能光标，光标处增加字符
			if(viewer->cursor_enable) {
				
				if (viewer->process_mode == CONSOLE_PRINT) {
					txtViewer_printf(viewer, L"%lc",viewer->getchar);
				} else {
					txtViewer_CursorAddChar(viewer,viewer->getchar);
				}
				
			} else { //否者在结尾处增加字符
				txtViewer_printf(viewer, L"%c",viewer->getchar);
			}	
		}
	}
	viewer->process(viewer);
	if(viewer->win_boundary) {
		txtViewer_drawBoundary(viewer);
	}

}


txtViewer_t txtViewer;

//////////////////////////////////////////////// 窗口控制API //////////////////////////////////////////////////
static bool scroll_down()
{
	txtViewer.txt_ofsetY++;
	return false;
}

static bool scroll_up()
{
	txtViewer.txt_ofsetY--;
	return false;
}

static bool scroll_left()
{
	txtViewer.txt_ofsetX--;
	return false;
}

static bool scroll_right()
{
	txtViewer.txt_ofsetX++;
	return false;
}

static bool win_up()
{
	txtViewer.window_y--;
	return false;
}
static bool win_down()
{
	txtViewer.window_y++;
	return false;
}
static bool win_left()
{
	txtViewer.window_x--;
	return false;
}
static bool win_right()
{
	txtViewer.window_x++;
	return false;
}

static bool cur_down()
{
	cursor_down(&txtViewer);
	return true;
}

static bool cur_up()
{
	cursor_up(&txtViewer);
	return true;
}

static bool cur_L()
{
	cursor_left(&txtViewer);
	return true;
}

static bool cur_R()
{
	cursor_right(&txtViewer);
	return true;
}

static bool cur_del()
{
	txtViewer_CursorDeleteChar(&txtViewer);
	return true;
}

static bool cur_add()
{
	static u8 i=0;
	txtViewer_CursorAddChar(&txtViewer,++i%10+'0');
	return true;
}

///////////////////////////////////////////// 字符解析任务 //////////////////////////////////////////////
typedef bool (* button_f)(void);
static button_f btndown = scroll_down;
static button_f btnup = scroll_up;


void txt_test_open(void)
{
	if(txtViewer.data_buf == NULL)
	{
		txtViewer_init(&txtViewer,1024,0,0,NORMAL);
	}
}

void txtViewer_draw()
{

	txtViewer.run(&txtViewer);
	
}

//////////////////////////////////////////////// TXT_Viewer 菜单选项 ///////////////////////////////////////////////

void up_down()
{
	txtViewer.scroll_enable=false;
	btndown = scroll_down;
	btnup = scroll_up;
	txt_test_open();
}
void left_right()
{
	txtViewer.scroll_enable=false;
	btndown = scroll_left;
	btnup = scroll_right;txt_test_open();
}
void win_upDown()
{
	btndown = win_down;
	btnup = win_up;txt_test_open();
}
void win_leftRight()
{
	btndown = win_left;
	btnup = win_right;txt_test_open();
}
void size48x64()
{
	txtViewer_setWindow(&txtViewer, 48,64);txt_test_open();
}

void size48x96()
{
	txtViewer_setWindow(&txtViewer, 48,96);txt_test_open();
}

void size32x64()
{
	txtViewer_setWindow(&txtViewer, 32,64);txt_test_open();
}
void sizefull()
{
	txtViewer_setWindow(&txtViewer, 64,128);txt_test_open();
	txtViewer.window_x = 0;
	txtViewer.window_y = 0;
}

static u8 i=0;
bool p_down()
{
	txtViewer_printf(&txtViewer, L"%d\r",i++);
	return true;
}
bool p_downln()
{
	
	txtViewer_printf(&txtViewer, L"hel\rlo\r%d\n",i++);
	return true;
}

bool p_up()
{
	txtViewer.scroll_enable = false;
	txtViewer.scroll_pixel++;
	return false;
}
void p_test()
{
	txtViewer_changeProcessMode(&txtViewer,CONSOLE_PRINT);
	btndown = p_down;
	btnup = p_up;
	txt_test_open();
}

void p_testln()
{
	txtViewer_changeProcessMode(&txtViewer,CONSOLE_PRINT);
	btndown = p_downln;
	btnup = p_up;
	txt_test_open();
}


void normal_print()
{
	txtViewer_changeProcessMode(&txtViewer,NORMAL);
	btndown = p_downln;
	btnup = p_down;
	txt_test_open();
}

void autobrk_print()
{
	txtViewer_changeProcessMode(&txtViewer,AUTO_BREAKLINE);
	btndown = p_downln;
	btnup = p_down;
	txt_test_open();
}

void normal()
{
	txtViewer_changeProcessMode(&txtViewer,NORMAL);
	up_down();
}

void autobrk()
{
	txtViewer_changeProcessMode(&txtViewer,AUTO_BREAKLINE);
	up_down();
}

void clear_buf()
{
	i=0;
	txt_test_open();
	txtViewer_clearDataBuf(&txtViewer);
}

void flter_lr()
{
	setFilterOut(&txtViewer);
	txt_test_open();
}

void kbd_mode()
{
	txtViewer.keyboard_mode = !txtViewer.keyboard_mode;
	txt_test_open();
}

void scroll_anim()
{
	txtViewer.scroll_anim = !txtViewer.scroll_anim;
	txt_test_open();
}

void cursor_updown()
{
	btndown = cur_down;
	btnup = cur_up;
	txt_test_open();
}

void cursor_LR()
{
	btndown = cur_R;
	btnup = cur_L;
	txt_test_open();
}

void cursor_add()
{
	btndown = cur_del;
	btnup = cur_add;
	txt_test_open();
}


