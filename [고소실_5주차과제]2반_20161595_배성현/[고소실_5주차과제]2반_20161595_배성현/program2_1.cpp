#include "my_solver.h"

void program2_1()
{
	FILE* fp_r, *fp_w;
	__int64 start, freq, end;
	float resultTime = 0;

	fp_r = fopen("sampling_table.txt", "r");
	if (fp_r == NULL) {
		printf("input file not found....\n");
		exit(0);
	}

	fp_w = fopen("pdf_table.txt", "w");

	/***************************************************/
	int numOfSample, i, j;
	double** func;//�Լ��� �׷��� ���� ����
	double prevh;
	double normalh;
	fscanf(fp_r, "%d %lf", &numOfSample, &prevh);
	func = (double**)malloc(sizeof(double*) * numOfSample);
	for (i = 0; i < numOfSample; i++)
	{
		func[i] = (double*)malloc(sizeof(double) * 2);
		fscanf(fp_r, "%lf %lf", &func[i][0], &func[i][1]);
	}
	
	double x0, xn;//x0�� ������ xn�� ����.
	double diff;
	int starti, lasti;
	x0 = func[0][0];
	xn = func[numOfSample - 1][0];//���۰� ���� �������༭ ���߿� ����ȭ �� �� ���.
	diff = xn - x0;
	for (i = 0; i < numOfSample; i++)//x���� ����ȭ ���ִ� for�� 
	{
		func[i][0] = (func[i][0] - x0) / diff;//����ȭ ����.
	}
	normalh = prevh / diff;//����ȭ �Ǿ��� ���� h����.

	double integralValue;//���а� �����ϴ� ����.
	integralValue = (func[0][1] + func[numOfSample - 1][1]);//���� �հ� ���� �� ������.
	for (i = 1; i < numOfSample - 1; i++)
	{
		integralValue += 2 * (func[i][1]);
	}
	integralValue = 0.5 * integralValue * normalh;//���а� ����.
	/***************************************************/

	for (i = 0; i < numOfSample; i++)
	{
		func[i][1] /= integralValue;//y�� ���а����� ������ Ȯ�� �е��Լ��� �������.
	}

	///////////////////////////////////////////////////////////////��� �κ�.
	integralValue = (func[0][1] + func[numOfSample - 1][1]);//���� �հ� ���� �� ������.
	for (i = 1; i < numOfSample - 1; i++)
	{
		integralValue += 2 * (func[i][1]);
	}
	integralValue = 0.5 * integralValue * normalh;
	printf("*** Integrating the pdf from 0.0 to 1.0 = %lf\n", integralValue);
	///////////////////////////////////////////////////////////////��� �κ�.
	lasti = 0;
	integralValue = 0;
	for (i = lasti; func[i][0]<=0.25; i++)
	{
		integralValue += func[i][1];
	}
	starti = lasti + 1;
	lasti = i-1;
	for (i = starti; i < lasti; i++)
	{
		integralValue += func[i][1];
	}
	integralValue = 0.5 * integralValue * normalh;
	printf("*** Integrating the pdf from 0.0 to 0.25 = %lf\n", integralValue);
	///////////////////////////////////////////////////////////////��� �κ�.
	integralValue = 0;
	for (i = lasti; func[i][0] <= 0.5; i++)
	{
		integralValue += func[i][1];
	}
	starti = lasti + 1;
	lasti = i - 1;
	for (i = starti+1; i < lasti; i++)
	{
		integralValue += func[i][1];
	}
	integralValue = 0.5 * integralValue * normalh;
	printf("*** Integrating the pdf from 0.25 to 0.5 = %lf\n", integralValue);
	///////////////////////////////////////////////////////////////��� �κ�.
	integralValue = 0;
	for (i = lasti; func[i][0] <= 0.75; i++)
	{
		integralValue += func[i][1];
	}
	starti = lasti + 1;
	lasti = i - 1;
	for (i = starti; i < lasti; i++)
	{
		integralValue += func[i][1];
	}
	integralValue = 0.5 * integralValue * normalh;
	printf("*** Integrating the pdf from 0.5 to 0.75 = %lf\n", integralValue);
	///////////////////////////////////////////////////////////////��� �κ�.
	integralValue = 0;
	for (i = lasti; i<numOfSample; i++)
	{
		integralValue += func[i][1];
	}
	starti = lasti + 1;
	lasti = i - 1;
	for (i = starti; i < lasti; i++)
	{
		integralValue += func[i][1];
	}
	integralValue = 0.5 * integralValue * normalh;
	printf("*** Integrating the pdf from 0.75 to 1.0 = %lf\n", integralValue);

	fprintf(fp_w, "%d %lf\n", numOfSample, normalh);
	for (i = 0; i < numOfSample; i++)
	{
		fprintf(fp_w, "%lf %lf\n", func[i][0], func[i][1]);
	}

	if (fp_r != NULL) fclose(fp_r);
	if (fp_w != NULL) fclose(fp_w);
}
