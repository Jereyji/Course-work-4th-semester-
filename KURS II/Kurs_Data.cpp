// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Kurs_Data.h"

void KURSII::Kurs_Data::Check_Visk_Data(int a, int b)
{
	if (b == 1 || b == 3 || b == 5 || b == 7 || b == 8 || b == 10 || b == 12) {
		if (a > 31 || a < 0)	MessageBox::Show("������� ���������� ����!", "������!");
	}
	else if (b == 4 || b == 6 || b == 9 || b == 11) {
		if (a > 30 || a < 0)	MessageBox::Show("������� ���������� ����!", "������!");
	}
	else if (b == 2) {
		if (a > 28 || a < 0)	MessageBox::Show("������� ���������� ����!", "������!");
	}
}

void KURSII::Kurs_Data::Check_Ne_Visk_Data(int a, int b)
{
	if (b == 1 || b == 3 || b == 5 || b == 7 || b == 8 || b == 10 || b == 12) {
		if (a > 31 || a < 0)	MessageBox::Show("������� ���������� ����!", "������!");
	}
	else if (b == 4 || b == 6 || b == 9 || b == 11) {
		if (a > 30 || a < 0)	MessageBox::Show("������� ���������� ����!", "������!");
	}
	else if (b == 2) {
		if (a > 29 || a < 0)	MessageBox::Show("������� ���������� ����!", "������!");
	}
}

void KURSII::Kurs_Data::WebCl(int a ,int b, int c)
{
	WebClient^ wb = gcnew WebClient();
	String^ line;

	if (a < 10 && b < 10) {
		line = wb->DownloadString("https://cbr.ru/scripts/XML_daily.asp?date_req=0" + a + "/0" + b + "/" + c);
	}
	else if (a < 10) {
		line = wb->DownloadString("https://cbr.ru/scripts/XML_daily.asp?date_req=0" + a + "/" + b + "/" + c);
	}
	else if (b < 10) {
		line = wb->DownloadString("https://cbr.ru/scripts/XML_daily.asp?date_req=" + a + "/0" + b + "/" + c);
	}
	else
	{
		line = wb->DownloadString("https://cbr.ru/scripts/XML_daily.asp?date_req=" + a + "/" + b + "/" + c);
	}

	Regex^ regex = gcnew Regex("<CharCode>" + comboBox1->Text + "</CharCode><Nominal>(.*?)</Nominal><Name>(.*?)</Name><Value>(.*?)</Value>");
	Match^ match = regex->Match(line);

	label4->Text = match->Groups[1]->Value + " " + comboBox1->Text + " = " + match->Groups[3]->Value + " RUB";
}

System::Void KURSII::Kurs_Data::����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("1. �������� ������\n2. �������� ���� (c 01.07.1992 - �� �.�.)\n3. ������� ������ - �������", "����������");
}

System::Void KURSII::Kurs_Data::���������������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MyForm^ form = gcnew MyForm();
	this->Hide();
	form->Show();
}

System::Void KURSII::Kurs_Data::������������������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Kurs_valut^ form = gcnew Kurs_valut();
	this->Hide();
	form->Show();
}

System::Void KURSII::Kurs_Data::�����ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
}

System::Void KURSII::Kurs_Data::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (textBox1->Text == "" || textBox2->Text == "" || textBox3->Text == "")
		MessageBox::Show("������� ����!", "������!");
	else {
		int a = Convert::ToInt16(textBox1->Text);
		int b = Convert::ToInt16(textBox2->Text);
		int c = Convert::ToInt16(textBox3->Text);

		if (c % 4 == 0) {
			Check_Ne_Visk_Data(a, b);

			WebCl(a, b, c);
		}
		else {
			Check_Visk_Data(a, b);

			WebCl(a, b, c);
		}
	}
	return System::Void();
}

