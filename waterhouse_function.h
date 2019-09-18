//update from 2018.11.07 

#pragma once

#include <iostream>
#include <string> 
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <vector>
#include <direct.h>
#include <io.h>
#include <tchar.h>

using namespace std;





//class names-------------------------------------------------------------------------

//http://alrightchiu.github.io/SecondRound/linked-list-xin-zeng-zi-liao-shan-chu-zi-liao-fan-zhuan.html
template <class CType> class ListNode;
template <class CType> class LinkedList;



//function names----------------------------------------------------------------------

void CountDownTimeSec(int input_sec);
bool IsInt(string str);
bool IsPosInt(string str);
bool IsAllAlphabet(string input_string);
bool IsFileExist(string input_file_name);
string IntToString(int input_int);
int StringToInt(std::string input_s){
	return stoi(input_s);
}
template <typename T>
std::string NumberToString (const T& input_num);
const wchar_t * StringToWchar_t(const string input_string);
string Wchar_tToString(const wchar_t * input_wchar_t);
const wchar_t * CharToWchar_t(const char * input_char);
const char * Wchar_tToChar(const wchar_t * input_wchar_t);
const char * TCHARToChar(const TCHAR * input_TCHAR);


void SafeCinInt(int & output);


void Appear2DString(vector<vector<string>> & input_2dstring);
bool ReadCsvTo2dString(string & csv_file_name, vector<vector<string>> & martix_data);
bool Write2dStringToCsv(string & csv_file_name, vector<vector<string>> & martix_data);


void CheckDir(char *, vector<vector<string>> &, string filter);
void GetOpeningFilePathName(string & choose_file_name, string mode1);
string GetOpeningFilePathNameByWindows();
/*http://www.sharejs.com/codes/cpp/6324
ofstream out("keys.txt", ios::out);
LRESULT CALLBACK KeyboardHookProc(int nCode, WPARAM wParam, LPARAM lParam) {
PKBDLLHOOKSTRUCT p = (PKBDLLHOOKSTRUCT)(lParam);
// If key is being pressed
if (wParam == WM_KEYDOWN) {
switch (p->vkCode) {
// Invisible keys
case VK_CAPITAL:    out << "<CAPLOCK>";     break;
case VK_SHIFT:      out << "<SHIFT>";       break;
case VK_LCONTROL:   out << "<LCTRL>";       break;
case VK_RCONTROL:   out << "<RCTRL>";       break;
case VK_INSERT:     out << "<INSERT>";      break;
case VK_END:        out << "<END>";         break;
case VK_PRINT:      out << "<PRINT>";       break;
case VK_DELETE:     out << "<DEL>";         break;
case VK_BACK:       out << "<BK>";          break;
case VK_LEFT:       out << "<LEFT>";        break;
case VK_RIGHT:      out << "<RIGHT>";       break;
case VK_UP:         out << "<UP>";          break;
case VK_DOWN:       out << "<DOWN>";        break;
// Visible keys
default:
cout << char(tolower(p->vkCode));
}
}
return CallNextHookEx(NULL, nCode, wParam, lParam);
}
*/
void Kcout(string & myout);


string GetStringFromEdit(const HWND input_hwnd);
void SetVectorStringToEdit(const vector<string> input_vector_string, const HWND target_hwnd);







//class member name---------------------------------------------------------------------

template <class CType> class ListNode {
private:
	CType data;
	ListNode<CType> * next;
public:
	~ListNode() {}
	ListNode() {}
	ListNode(CType input_data) :data(input_data), next(0) {}
	ListNode(const ListNode<CType> & input_node) {
		data = input_node.data;
		next = input_node.next;
	}
	ListNode(ListNode<CType> && input_node) {
		data = input_node.data;
		next = input_node.next;
		input_node.data = 0;
		input_node.next = nullptr;
	}
	ListNode<CType> & operator = (const ListNode<CType> & input_node) {
		data = input_node.data;
		next = input_node.next;
		return *this;
	}
	ListNode<CType> & operator=(ListNode<CType> && input_node) {
		data = input_node.data;
		next = input_node.next;
		input_node.data = 0;
		input_node.next = nullptr;
		return *this;
	}
	friend class LinkedList<CType>;
};
template <class CType> class LinkedList {
private:
	// int size;                // size是用來記錄Linked list的長度, 非必要
	ListNode<CType> *first;            // list的第一個node
public:
	LinkedList() :first(0) {};
	//copy constructor
	//assignment constructor
	//move copy constructor
	//move assignment constructor
	void PrintList();           // 印出list的所有資料
	void Push_front(CType x);     // 在list的開頭新增node
	void Push_back(CType x);      // 在list的尾巴新增node
	bool Delete(CType x);         // 刪除list中的 int x
	void Clear();               // 把整串list刪除
};







//class member content-----------------------------------------------------------------

template <class CType> void LinkedList<CType>::Push_front(CType x) {
	ListNode<CType> * newNode = new ListNode(x);   // 配置新的記憶體
	newNode->next = first;                 // 先把first接在newNode後面
	first = newNode;                       // 再把first指向newNode所指向的記憶體位置
}
template <class CType> void LinkedList<CType>::Push_back(CType x) {
	ListNode<CType> * newNode = new ListNode(x);   // 配置新的記憶體
	if (first == 0) {                      // 若list沒有node, 令newNode為first
		first = newNode;
		return;
	}
	ListNode *current = first;
	while (current->next != 0) {           // Traversal
		current = current->next;
	}
	current->next = newNode;               // 將newNode接在list的尾巴
}
template <class CType> bool LinkedList<CType>::Delete(CType x) {
	ListNode<CType> * current = first;
	ListNode<CType> * previous = 0;
	while (current != 0 && current->data != x) {  // Traversal
		previous = current;                       // 如果current指向NULL
		current = current->next;                  // 或是current->data == x
	}                                             // 即結束while loop
	if (current == 0) {                 // list沒有要刪的node, 或是list為empty
		return false;
		// return;
	}
	else if (current == first) {        // 要刪除的node剛好在list的開頭
		first = current->next;          // 把first移到下一個node
		delete current;                 // 如果list只有一個node, 那麼first就會指向NULL
		current = 0;                    // 當指標被delete後, 將其指向NULL, 可以避免不必要bug
		// return;                     
	}
	else {                              // 其餘情況, list中有欲刪除的node, 
		previous->next = current->next; // 而且node不為first, 此時previous不為NULL
		delete current;
		current = 0;
		// return;
	}
	return true;
}
template <class CType> void LinkedList<CType>::Clear() {
	while (first != 0) {            // Traversal
		ListNode *current = first;
		first = first->next;
		delete current;
		current = 0;
	}
}






//function content-----------------------------------------------------------------

void PreCin(string input_string) {

}
void CountDownTimeSec(int input_sec) {
	while (1) {
		cout << " >> " << input_sec;
		Sleep(1000);
		input_sec = input_sec - 1;
		if (input_sec <= 0) { cout << " >> 0 " << endl; break; }
	}
}
bool IsInt(string str) {
	stringstream sin(str);
	int i;
	char c;
	if (!(sin >> i)) { return false; }
	if (sin >> c) { return false; }
	return true;
}
bool IsPosInt(string str) {
	stringstream sin(str);
	int i;
	char c;
	if (!(sin >> i)) { return false; }
	if (i <= 0) { return false; }
	if (sin >> c) { return false; }
	return true;
}
bool IsAllAlphabet(string input_string) {
	for (int index2 = 0; index2 < input_string.size(); index2++) {
		if (!isalpha(input_string[index2])) {
			return false;
		}
	}
	return true;
}
bool IsFileExist(string input_file_name) {
	struct stat buf;
	int i = stat(input_file_name.c_str(), &buf);
	/* File found */
	if (i == 0)
	{
		return 1;
	}
	return 0;
}
string IntToString(int input_int) {
	if (input_int == 0) { return "0"; }
	stringstream ss;
	ss << input_int;
	string output_string = ss.str();
	return output_string;
}
template <typename T>
std::string NumberToString ( const T& input_num ){
	std::ostringstream ss;
	ss << input_num;
	return ss.str();
}
const wchar_t * StringToWchar_t(const string input_string) {
	const wchar_t * output_wchar_t = 0;
	output_wchar_t = CharToWchar_t(input_string.c_str());
	return output_wchar_t;
}
string Wchar_tToString(const wchar_t * input_wchar_t) {
	const char * temp_char = 0;
	temp_char = Wchar_tToChar(input_wchar_t);
	string output_string(temp_char);
	return output_string;
}
const wchar_t * CharToWchar_t(const char * input_char)
{
	const size_t input_size = strlen(input_char) + 1;
	wchar_t * output_wchar_t = new wchar_t[input_size];
	size_t output_size;
	mbstowcs_s(& output_size, output_wchar_t, input_size, input_char, input_size - 1);
	return output_wchar_t;
}
const char * Wchar_tToChar(const wchar_t * input_wchar_t) {

	size_t input_length = wcslen(input_wchar_t) + 1;
	size_t convertedChars = 0;

	const size_t output_size = input_length * 2;
	char * output_char = new char[output_size];

	wcstombs_s(&convertedChars, output_char, output_size, input_wchar_t, _TRUNCATE);
	
	return  output_char;
	//原文：https ://blog.csdn.net/ghevinn/article/details/9825727 
}
const char * TCHARToChar(const TCHAR * input_TCHAR) {
	
#ifdef UNICODE
	//一樣求size
	int ansiSize = WideCharToMultiByte(CP_ACP, 0, input_TCHAR, -1, NULL, 0, NULL, false);
	//使用剛剛求出的size建立字串
	char* ansiStr = new char[ansiSize + 1];
	//將寬字元字串寫入字串
	WideCharToMultiByte(CP_ACP, 0, input_TCHAR, -1, ansiStr, ansiSize, NULL, false);
	return ansiStr;
	/*/
	// Simple C
	const size_t size = ( wcslen(text) + 1 ) * sizeof(wchar_t);
	wcstombs(&buffer[0], text, size);
	std::vector<char> buffer(size);
	/*/
	// Windows API (I would use this)
	//std::vector<char> buffer;
	//int size = WideCharToMultiByte(CP_UTF8, 0, buf, -1, NULL, 0, NULL, NULL);
	//if (size > 0) {
	//	buffer.resize(size);
	//	WideCharToMultiByte(CP_UTF8, 0, buf, -1, static_cast<BYTE*>(&buffer[0]), buffer.size(), NULL, NULL);
	//}
	//else {
	//	// Error handling
	//}

	
#else
	return input_TCHAR;
#endif

}


void SafeCinInt(int & output) {
	while (1) {
		string temp_cin_string;
		cin >> temp_cin_string;
		if (temp_cin_string == "0") { output = stoi(temp_cin_string); return; }
		if (stoi(temp_cin_string) && (stoi(temp_cin_string) == (int)stoi(temp_cin_string))) {
			output = stoi(temp_cin_string);
			return;
		}
	}
}


void Appear2DString(vector<vector<string>> & input_2dstring) {
	for (int index2 = 0; index2 < input_2dstring.size(); index2++) {
		for (int index3 = 0; index3 < input_2dstring[index2].size(); index3++) {
			cout << input_2dstring[index2][index3] << ", ";
		}
		cout << endl;
	}
}
bool ReadCsvTo2dString(string & csv_file_name, vector<vector<string>> & martix_data) {
	//readfile
	if (!IsFileExist(csv_file_name)) { return false; }
	martix_data.clear();
	fstream file;
	file.open(csv_file_name);
	string line;
	int index1 = 0;
	while (getline(file, line, '\n')) {//讀檔讀到跳行字元
		index1 = index1 + 1;
		cout << "reading data: no." << index1 << " row." << endl;
		istringstream templine(line); // string 轉換成 stream
		vector<string> one_row_data;
		one_row_data.resize(5);
		string data;
		for (int index2 = 0; getline(templine, data, ','); index2++) {
			if (index2 < one_row_data.size()) { one_row_data[index2] = data; }
			else { one_row_data.push_back(data); }
		}
		martix_data.push_back(one_row_data);
	}
	file.close();
	cout << "read OK" << endl;
	return true;
}
bool Write2dStringToCsv(string & csv_file_name, vector<vector<string>> & martix_data) {
	ofstream file;
	file.open(csv_file_name);
	for (int index1 = 0; index1 < martix_data.size(); index1++) {
		cout << index1 << " : ";
		for (int index2 = 0; index2 < martix_data[index1].size(); index2++) {
			file << martix_data[index1][index2] << ",";
			cout << martix_data[index1][index2] << ",";
		}
		file << endl;
		cout << endl;
	}
	cout << " it's alright." << endl;
	file.close();
	return true;
}


void CheckDir(char * buf, vector<vector<string>> & content_of_folder, string filter = "*.*") {

	/*
	char buf[2000];
	_getcwd(buf, sizeof(buf) - 1);
	cout <<"current directory: "<< buf << endl;
	*/

	char attrib[_MAX_FNAME];
	char file_name[_MAX_FNAME];

	cout << "current search condition in filename extension is " << filter << endl;
	/*
	while (1) {

	cout << "keybroad 1 to cancel the search" << endl;
	cout << "keybroad 2 to search directory in current directory" << endl;
	cout << "keybroad 3 to change the search condition for directory" << endl;
	int directive = 0;
	cin >> directive;
	if (directive == 1) { return; }
	if (directive == 2) { break; }
	if (directive == 3) {
	cout << "keybroad the new condition: (ex: keyin *.jpg for search jpg file)" << endl;
	string tmp_change_filter;
	cin >> tmp_change_filter;
	if (sizeof(tmp_change_filter) / sizeof(tmp_change_filter[0]) > 2
	|| tmp_change_filter[0] == '*'
	|| tmp_change_filter[1] == '.') {
	filter = tmp_change_filter;
	}
	else {
	cout << "the input condition (" << tmp_change_filter << ") is error!" << endl;
	continue;
	}
	}
	}
	*/

	content_of_folder.clear();
	struct _finddata_t file;
	intptr_t hFile;
	hFile = _findfirst(filter.c_str(), &file);
	if (hFile != -1) {
		do {
			//get filename
			vector<string> tmp_attrib;
			tmp_attrib.clear();
			tmp_attrib.push_back(file.name);
			sprintf_s(file_name, "%s\\%s", buf, file.name);
			//printf("%s\n", file_name);

			memset((void*)attrib, 0, _MAX_FNAME);
			// file attribute
			sprintf_s(attrib, "\tattrib:[ ");
			if (file.attrib & _A_ARCH) {
				tmp_attrib.push_back("_A_ARCH");
				strcat_s(attrib, "檔案 ");
			}
			if (file.attrib & _A_HIDDEN) {
				tmp_attrib.push_back("_A_HIDDEN");
				strcat_s(attrib, "隱藏 ");
			}
			if (file.attrib & _A_NORMAL) {
				tmp_attrib.push_back("_A_NORMAL");
				strcat_s(attrib, "普通 ");
			}
			if (file.attrib & _A_RDONLY) {
				tmp_attrib.push_back("_A_RDONLY");
				strcat_s(attrib, "唯讀 ");
			}
			if (file.attrib & _A_SUBDIR) {
				tmp_attrib.push_back("_A_SUBDIR");
				strcat_s(attrib, "資料夾 ");
			}
			if (file.attrib & _A_SYSTEM) {
				tmp_attrib.push_back("_A_SYSTEM");
				strcat_s(attrib, "系統 ");
			}
			strcat_s(attrib, "]");
			//printf("%s\n", attrib);
			//printf("\tfilesize:%u\n", file.size);
			content_of_folder.push_back(tmp_attrib);
		} while (_findnext(hFile, &file) == 0);
		_findclose(hFile);
	}
}
void GetOpeningFilePathName(string & choose_file_name, string mode1 = "test") {

	if (mode1 != "test") { cin.putback(mode1[0]); }
	char buf[2000];
	while (1) {
		_getcwd(buf, sizeof(buf) - 1);
		cout << "current directory: " << buf << endl;
		vector<vector<string>> content_of_folder;
		CheckDir(buf, content_of_folder);

		cout << "The following are files in current directory: " << endl;
		for (int i = 0; i < content_of_folder.size(); i++) {
			cout << "number " << i << " : " << content_of_folder[i][0];
			cout << ", attrib: " << content_of_folder[i][1] << endl;
		}

		cout << "choose number to choose target file or open the folder" << endl;
		string temp_cin;
		cin >> temp_cin;
		int temp_cin_num = 0;
		if (temp_cin == "t") { choose_file_name = "t11.tiff"; return; }
		if (atoi(temp_cin.c_str()) && atoi(temp_cin.c_str()) > 0) {
			temp_cin_num = atoi(temp_cin.c_str());
			if (content_of_folder[temp_cin_num][1] == "_A_SUBDIR") {
				strcat_s(buf, "\\");
				strcat_s(buf, content_of_folder[temp_cin_num][0].c_str());
				cout << buf << endl;
				_chdir(buf);
				continue;
			}
			choose_file_name = content_of_folder[temp_cin_num][0];
			cout << "The file chosen: " << choose_file_name << ", enter y/n" << endl;
			cin >> temp_cin;
			if (temp_cin == "y") { return; }
			else { continue; }
		}
	}
}
string GetOpeningFilePathNameByWindows() {
	//     
	OPENFILENAME ofn;      // 公共对话框结构。   
	TCHAR szFile[MAX_PATH]; // 保存获取文件名称的缓冲区。             
	// 初始化选择文件对话框。   
	ZeroMemory(&ofn, sizeof(OPENFILENAME));
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = _T("All(*.*)\0*.*\0Text(*.txt)\0*.TXT\0\0");
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	//ofn.lpTemplateName =  MAKEINTRESOURCE(ID_TEMP_DIALOG);  
	// 显示打开选择文件对话框。   

	if (GetOpenFileName(&ofn))
	{
		//显示选择的文件。   
		OutputDebugString(szFile);
		OutputDebugString(_T("\r\n"));
		return TCHARToChar(szFile);;
	}
}
void Kcout(string & myout) {
	for (int i = 0; i<myout.length(); i++)
	{
		switch (myout[i])
		{
			/*
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
			case '0':
			keybd_event(VkKeyScan(myout[i]), 0, 0, 0); //depress
			keybd_event(VkKeyScan(myout[i]), 0, KEYEVENTF_KEYUP, 0); // release!
			break;
			*/
		case '!':
		case '@':
		case '#':
		case '$':
		case '^':
		case '&':
		case '*':
		case '(':
		case ')':
		case '_':
		case '+':
		case '~':
		case '{':
		case '}':
		case '|':
		case '"':
		case ':':
		case '<':
		case '>':
		case '?':
		case 'A':
		case 'B':
		case 'C':
		case 'D':
		case 'E':
		case 'F':
		case 'G':
		case 'H':
		case 'I':
		case 'J':
		case 'K':
		case 'L':
		case 'M':
		case 'N':
		case 'O':
		case 'P':
		case 'Q':
		case 'R':
		case 'S':
		case 'T':
		case 'U':
		case 'V':
		case 'W':
		case 'X':
		case 'Y':
		case 'Z':
		case '%':
			keybd_event(VK_SHIFT, 0x10, 0, 0); // shift depress
			keybd_event(VkKeyScan(myout[i]), 0, 0, 0); //depress
			keybd_event(VkKeyScan(myout[i]), 0, KEYEVENTF_KEYUP, 0); // release!
			keybd_event(VK_SHIFT, 0x10, KEYEVENTF_KEYUP, 0);// shift release
			break;

		default:
			keybd_event(VkKeyScan(myout[i]), 0, 0, 0); //depress
			keybd_event(VkKeyScan(myout[i]), 0, KEYEVENTF_KEYUP, 0); // release!
			break;
		}
	}
}


string GetStringFromEdit(const HWND input_hwnd) {
	TCHAR buf[1024];
	SendMessage(input_hwnd, WM_GETTEXT, sizeof(buf) / sizeof(TCHAR), (LPARAM)(void*)buf);
	return TCHARToChar(buf);
}
void SetVectorStringToEdit(const vector<string> input_vector_string, const HWND target_hwnd) {
	string output_multiline_string;
	for (int index1 = 0; index1 < input_vector_string.size(); index1++) {
		output_multiline_string = output_multiline_string + input_vector_string[index1] + "\r\n";
	}
	SendMessage(target_hwnd, WM_SETTEXT, 1, (LPARAM)output_multiline_string.c_str());
}






