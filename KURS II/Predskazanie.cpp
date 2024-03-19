// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Predskazanie.h"
#include "MyForm.h"

void KURSII::Predskazanie::A_Check(int& day, int& month, const int year)
{
	if (month == 12 && day > 31) {
		day = 1;
		month = 1;
	}
	else if (month == 1 && day > 31) {
		day = 1;
		month = 2;
	}
	else if (month == 2 && year / 4 == 0 && day > 29) {
		day = 1;
		month = 3;
	}
	else if (month == 2 && year / 4 != 0 && day > 28) {
		day = 1;
		month = 3;
	}
	else if (month == 3 && day > 31) {
		day = 1;
		month = 4;
	}
	else if (month == 4 && day > 30) {
		day = 1;
		month = 5;
	}
	else if (month == 5 && day > 31) {
		day = 1;
		month = 6;
	}
	else if (month == 6 && day > 30) {
		day = 1;
		month = 7;
	}
	else if (month == 7 && day > 31) {
		day = 1;
		month = 8;
	}
	else if (month == 8 && day > 31) {
		day = 1;
		month = 9;
	}
	else if (month == 9 && day > 30) {
		day = 1;
		month = 10;
	}
	else if (month == 10 && day > 31) {
		day = 1;
		month = 11;
	}
	else if (month == 11 && day > 30) {
		day = 1;
		month = 12;
	}
}

void KURSII::Predskazanie::method_spros_predl(double kurs, Match^ match, double mnozh)
{
	WebClient^ wb = gcnew WebClient();
	String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_daily.asp?");

	Regex^ regex0 = gcnew Regex("<ValCurs Date=\"(.*?)\" name");
	Match^ match0 = regex0->Match(line);

	String^ Today_data = match0->Groups[1]->Value;
	String^ day;
	String^ month;
	String^ year;

	for (int i = 0; i < 10; i++) {
		if (Today_data[i] != '.' && i < 3)
			day += Today_data[i];
		if (Today_data[i] != '.' && i > 2 && i < 5)
			month += Today_data[i];
		if (Today_data[i] != '.' && i > 5)
			year += Today_data[i];
	}
	
	int da = System::Convert::ToInt32(day);
	int mon = System::Convert::ToInt32(month);
	int yea = System::Convert::ToInt32(year);

	// kurs = System::Convert::ToDouble(match->Groups[3]->Value);
	kurs = kurs + (spros - predl) * mnozh;
	label4->Text = match->Groups[1]->Value + " " + comboBox1->Text + " = " + kurs + " RUB";

	for (int i = 0; i < 11; i++) {
		A_Check(da, mon, yea); // �������� ���� �� ������������

		kurs = kurs + (spros - predl) * 0.034;
		this->chart2->Series[0]->Points->AddXY(da + "." + mon + "." + yea, kurs);
		da++;
	}
}

void KURSII::Predskazanie::method_ucheta_PPS(double kurs, Match^ match, double inf_2)
{
	WebClient^ wb = gcnew WebClient();
	String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_daily.asp?");

	Regex^ regex0 = gcnew Regex("<ValCurs Date=\"(.*?)\" name");
	Match^ match0 = regex0->Match(line);

	String^ Today_data = match0->Groups[1]->Value;
	String^ day;
	String^ month;
	String^ year;

	for (int i = 0; i < 10; i++) {
		if (Today_data[i] != '.' && i < 3)
			day += Today_data[i];
		if (Today_data[i] != '.' && i > 2 && i < 5)
			month += Today_data[i];
		if (Today_data[i] != '.' && i > 5)
			year += Today_data[i];
	}
	int yea = System::Convert::ToInt32(year);
	
	// kurs = System::Convert::ToDouble(match->Groups[3]->Value);
	predz = ((inf_RUB - inf_2) / 100 + 1) * kurs;

	yea++;

	label4->Text = match->Groups[1]->Value + " " + comboBox1->Text + " = " + predz + " RUB";
	this->chart2->Series[0]->Points->AddXY(Today_data, kurs);
	this->chart2->Series[0]->Points->AddXY(day + "." + month + "." + yea, predz);
	
}

System::Void KURSII::Predskazanie::����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("1.�������� ������\n2.������� ������ - �������", "����������");
}

System::Void KURSII::Predskazanie::���������������������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MyForm^ form = gcnew MyForm();
	this->Hide();
	form->Show();
}

System::Void KURSII::Predskazanie::�����ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
}

System::Void KURSII::Predskazanie::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	this->chart2->Series[0]->Points->Clear();
	WebClient^ wb = gcnew WebClient();
	String^ line = wb->DownloadString("https://cbr.ru/scripts/XML_daily.asp?");
	Regex^ regex = gcnew Regex("<CharCode>" + comboBox1->Text + "</CharCode><Nominal>(.*?)</Nominal><Name>(.*?)</Name><Value>(.*?)</Value>");
	Match^ match = regex->Match(line);

	// ����� ����� ���
	if (comboBox2->Text == "����� ����� ���") {
		if (comboBox1->Text == "USD") {
			method_ucheta_PPS(USD, match, inf_USD);
		}
		else if (comboBox1->Text == "EUR") {
			method_ucheta_PPS(EUR, match, inf_EUR);
		}
		else if (comboBox1->Text == "KZT") {
			method_ucheta_PPS(KZT, match, inf_KZT);
		}
		else if (comboBox1->Text == "UAH") {
			method_ucheta_PPS(UAH, match, inf_UAH);
		}
	}
	// ����� ������ � �����������
	else if (comboBox2->Text == "����� ������ � �����������") {
		srand(time(0));
		spros = (spros + predl) / spros * predl;
		predl = (spros + predl) / spros * predl;
		if (comboBox1->Text == "USD") {
			x = 0;
			method_spros_predl(USD, match, mnozh_USD);
		}
		else if (comboBox1->Text == "EUR") {
			x = 0;
			method_spros_predl(EUR, match, mnozh_EUR);
		}
		else if (comboBox1->Text == "KZT") {
			x = 0;
			method_spros_predl(KZT, match, mnozh_KZT);
		}
		else if (comboBox1->Text == "UAH") {
			x = 0;
			method_spros_predl(UAH, match, mnozh_UAH);
		}
	}
	//........................................................................................

	return System::Void();
}
