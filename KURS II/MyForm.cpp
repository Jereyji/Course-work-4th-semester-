// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "MyForm.h"
#include "Kurs_valut.h"
#include "Predskazanie.h"
#include "Kurs_Data.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	KURSII::MyForm form;
	Application::Run(% form);

}

System::Void KURSII::MyForm::button1_Click(System::Object^ sender, System::EventArgs^ e)
{
	Kurs_valut^ form = gcnew Kurs_valut();
	this->Hide();
	form->Show(); 
}

System::Void KURSII::MyForm::button2_Click(System::Object^ sender, System::EventArgs^ e)
{
	Predskazanie^ form = gcnew Predskazanie();
	this->Hide();
	form->Show();
}

System::Void KURSII::MyForm::����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("1.�������� ������\n2.�������", "����������");
}

System::Void KURSII::MyForm::����������ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	MessageBox::Show("������ ��������� ���������� ������� ���� �����, � ����� ����� ������������� ���� ������!", "�� ���������");
} 

System::Void KURSII::MyForm::�����ToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
{
	Application::Exit();
}
