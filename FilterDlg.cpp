
// FilterDlg.cpp: файл реализации
//

#include "stdafx.h"
#include "Filter.h"
#include "FilterDlg.h"
#include "afxdialogex.h"

#include <ctime>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CFilterDlg

CFilterDlg::CFilterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FILTER_DIALOG, pParent)
	, percentNoise(10)
	, _A1(100)
	, _A2(150)
	, _A3(250)
	, _x1(30)
	, _y1(30)
	, _sx1(10)
	, _sy1(10)
	, _x2(100)
	, _y2(100)
	, _sx2(20)
	, _sy2(20)
	, _x3(300)
	, _y3(350)
	, _sx3(20)
	, _sy3(20)
	, _heightGauss(490)
	, _widthGauss(500)
	, _radioOriginal(1)
	, _radioNoised(0)
	, _isLog(FALSE)
	, _isBatterworth(FALSE)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC1, _picture1);
	DDX_Control(pDX, IDC_DPI, _dpiText);
	DDX_Control(pDX, IDC_DPI_NEW, _dpiTextNew);
	DDX_Text(pDX, IDC_EDIT1, percentNoise);
	DDX_Control(pDX, IDC_PIC2, _picture2);
	DDX_Text(pDX, IDC_A1, _A1);
	DDX_Text(pDX, IDC_A2, _A2);
	DDX_Text(pDX, IDC_A3, _A3);
	DDX_Text(pDX, IDC_X1, _x1);
	DDX_Text(pDX, IDC_Y1, _y1);
	DDX_Text(pDX, IDC_SIGMAX1, _sx1);
	DDX_Text(pDX, IDC_SIGMAY1, _sy1);
	DDX_Text(pDX, IDC_X2, _x2);
	DDX_Text(pDX, IDC_Y2, _y2);
	DDX_Text(pDX, IDC_SIGMAX2, _sx2);
	DDX_Text(pDX, IDC_SIGMAY2, _sy2);
	DDX_Text(pDX, IDC_X3, _x3);
	DDX_Text(pDX, IDC_Y3, _y3);
	DDX_Text(pDX, IDC_SIGMAX3, _sx3);
	DDX_Text(pDX, IDC_SIGMAY3, _sy3);
	DDX_Text(pDX, IDC_HEIGHTG, _heightGauss);
	DDX_Text(pDX, IDC_WIDTHG, _widthGauss);
	DDX_Radio(pDX, IDC_RADIO_ORIG, _radioOriginal);
	DDX_Radio(pDX, IDC_RADIO_N, _radioNoised);
	DDX_Control(pDX, IDC_SLIDER_R, _sliderR);
	DDX_Control(pDX, IDC_RADIUS, _radiusText);
	DDX_Control(pDX, IDC_ETHRES, _threshholdEnergyText);
	DDX_Control(pDX, IDC_SQ_DEV, _squarenessDevText);
	DDX_Check(pDX, IDC_LOG, _isLog);
	DDX_Control(pDX, IDC_SQ_DEV2, _squarenessDevOrigNoisedText);
	DDX_Check(pDX, IDC_CHECK1, _isBatterworth);
}

BEGIN_MESSAGE_MAP(CFilterDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOAD, &CFilterDlg::OnBnClickedLoad)
	ON_BN_CLICKED(IDC_SPECTRE, &CFilterDlg::OnBnClickedSpectre)
	ON_BN_CLICKED(IDC_GAUSS, &CFilterDlg::OnBnClickedGauss)
	ON_BN_CLICKED(IDC_ENERGY, &CFilterDlg::OnBnClickedEnergy)
	ON_BN_CLICKED(IDC_TOIMAGE, &CFilterDlg::OnBnClickedToimage)
	ON_BN_CLICKED(IDC_RADIO_ORIG, &CFilterDlg::OnBnClickedRadioOrig)
	ON_BN_CLICKED(IDC_RADIO_N, &CFilterDlg::OnBnClickedRadioN)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_LOG, &CFilterDlg::OnBnClickedLog)
	ON_BN_CLICKED(IDC_CHECK1, &CFilterDlg::OnBnClickedCheck1)
END_MESSAGE_MAP()


// Обработчики сообщений CFilterDlg

BOOL CFilterDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	srand(time(NULL));
	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CFilterDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CFilterDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CFilterDlg::OnBnClickedLoad()
{
	UpdateData(TRUE);
	LoadPicture();
	if (_radioOriginal == 0) OnBnClickedRadioOrig();
	else OnBnClickedRadioN();
}

void CFilterDlg::LoadPicture()
{
	CFileDialog fd(true, NULL, NULL, OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY |
		OFN_LONGNAMES | OFN_PATHMUSTEXIST, _T("Image Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), NULL, 0, TRUE);

	if (fd.DoModal() != IDOK)
	{
		MessageBox(L"ERROR!!!", L"Error opening picture file.", MB_ICONERROR);
	};

	CString pathBMP = fd.GetPathName();
	Bitmap bmp(pathBMP);
	int width = bmp.GetWidth();
	int height = bmp.GetHeight();
	_image.clear();

	for (size_t i = 0; i < height; i++)
	{
		std::vector<double> bufPix;
		for (size_t j = 0; j < width; j++)
		{
			double value;
			Color color;
			bmp.GetPixel(j, height - i - 1, &color);
			value = 0.299*color.GetRed() + 0.587*color.GetGreen() + 0.114*color.GetBlue();
			bufPix.push_back(value);
		}
		_image.push_back(bufPix);
	}
	_imageNoised = _image;
	AddNoise();
	//AddZeroToPicture(_image);
	//AddZeroToPicture(_imageNoised);
	InterpolateImage(_image);
	InterpolateImage(_imageNoised);
	NormilizeAmplitude(_image, 0, 0);
	NormilizeAmplitude(_imageNoised, 0, 0);
	InitializeSlider();
}

bool CFilterDlg::CheckBin(int value, int &newvalue)
{
	bool result;
	int tempVal = value;
	if (tempVal <= 0)
		return false;
	while ((tempVal % 2) == 0)
	{
		if ((tempVal /= 2) == 1)
		{
			newvalue = tempVal;
			return true;
		}
	}

	int initValue = 1;
	while (initValue <= value)
	{
		initValue *= 2;
	}
	newvalue = initValue;

	return false;
}

void CFilterDlg::AddZeroToPicture(std::vector<std::vector<double>> &image)
{
	int width = image[0].size(),
		height = image.size(),
		newWidth = 0, newHeight = 0;

	CheckBin(width, newWidth);
	CheckBin(height, newHeight);

	for (size_t i = 0; i < height; i++)
	{
		for (size_t j = width; j < newWidth; j++)
		{
			image[i].push_back(0);
		}
	}

	for (size_t i = height; i < newHeight; i++)
	{
		std::vector<double> bufVec;
		for (size_t j = 0; j < newWidth; j++)
		{
			bufVec.push_back(0);
		}
		image.push_back(bufVec);
	}

	CString str, arg1, arg2;
	str = "Resolution: ";
	arg1.Format(_T("%d"), width);
	arg2.Format(_T("%d"), height);
	str += arg1 + "x" + arg2;
	_dpiText.SetWindowTextW(str);

	CString str2, arg3, arg4;
	str2 = "New resolution: ";
	arg3.Format(_T("%d"), newWidth);
	arg4.Format(_T("%d"), newHeight);
	str2 += arg3 + "x" + arg4;
	_dpiTextNew.SetWindowTextW(str2);
}

void CFilterDlg::AddNoise()
{
	std::vector < std::vector < double >> noise;

	int width = _imageNoised[0].size();
	int height = _imageNoised.size();

	for (size_t i = 0; i < height; i++)
	{
		std::vector<double> buf;
		for (size_t j = 0; j < width; j++)
		{
			double M, ksi, noiseVal;
			M = (double)(rand() % 9 + 12.0);
			ksi = 0.0;
			for (int k = 1; k <= M; k++)
			{
				ksi += (double)((rand() % 21 - 10.0) / 10.0);
			}
			noiseVal = (double)(ksi / M);
			buf.push_back(noiseVal);
		}
		noise.push_back(buf);
	}

	double EnergyImage = 0, EnergyNoise = 0;

#pragma omp parallel for reduction(+:EnergyImage, EnergyNoise)
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			EnergyImage += _image[i][j] * _image[i][j];
			EnergyNoise += noise[i][j] * noise[i][j];
		}
	}

	double alfa = sqrt(EnergyImage / EnergyNoise * percentNoise / 100.0);
#pragma omp parallel for
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			_imageNoised[i][j] = _image[i][j] + alfa * noise[i][j];
			if (_imageNoised[i][j] < 0) _imageNoised[i][j] = 0;
		}
	}
	CString str;
	str.Format(_TEXT("%.4f"), SquareDeviation(_image, _imageNoised));
	_squarenessDevOrigNoisedText.SetWindowTextW(str);
}

void CFilterDlg::Fourie1D(std::vector<cmplx> *data, int n, int is)
{
	int i, j, istep;
	int m, mmax;
	float r, r1, theta, w_r, w_i, temp_r, temp_i;
	float pi = 3.1415926f;

	r = pi * is;
	j = 0;
	for (i = 0; i < n; i++)
	{
		if (i < j)
		{
			temp_r = (*data)[j].real;
			temp_i = (*data)[j].image;
			(*data)[j].real = (*data)[i].real;
			(*data)[j].image = (*data)[i].image;
			(*data)[i].real = temp_r;
			(*data)[i].image = temp_i;
		}
		m = n >> 1;
		while (j >= m) { j -= m; m = (m + 1) / 2; }
		j += m;
	}
	mmax = 1;
	while (mmax < n)
	{
		istep = mmax << 1;
		r1 = r / (float)mmax;
		for (m = 0; m < mmax; m++)
		{
			theta = r1 * m;
			w_r = (float)cos((double)theta);
			w_i = (float)sin((double)theta);
			for (i = m; i < n; i += istep)
			{
				j = i + mmax;
				temp_r = w_r * (*data)[j].real - w_i * (*data)[j].image;
				temp_i = w_r * (*data)[j].image + w_i * (*data)[j].real;
				(*data)[j].real = (*data)[i].real - temp_r;
				(*data)[j].image = (*data)[i].image - temp_i;
				(*data)[i].real += temp_r;
				(*data)[i].image += temp_i;
			}
		}
		mmax = istep;
	}
	if (is > 0)
		for (i = 0; i < n; i++)
		{
			(*data)[i].real /= (float)n;
			(*data)[i].image /= (float)n;
		}


}

void CFilterDlg::Fourie2D(std::vector<std::vector<cmplx>> &data, int is)
{
	int width = data[0].size();
	int height = data.size();
#pragma omp parallel for
	for (int i = 0; i < height; i++)
	{
		Fourie1D(&data[i], width, is);
	}

	std::vector<std::vector<cmplx>> bufRes;
	for (int i = 0; i < width; i++)
	{
		std::vector<cmplx> buffer;
		for (int j = 0; j < height; j++)
		{
			buffer.push_back(data[j][i]);
		}
		bufRes.push_back(buffer);
	}

#pragma omp parallel for
	for (int i = 0; i < width; i++)
	{
		Fourie1D(&bufRes[i], height, is);
	}

	data.clear();
	data = bufRes;
}


void CFilterDlg::OnBnClickedSpectre()
{
	std::vector<std::vector<cmplx>> image;
	int width = _imageNoised[0].size();
	int height = _imageNoised.size();
	_imageSpectre.clear();
	_imageSpectreLog.clear();

	for (int i = 0; i < height; i++)
	{
		std::vector<cmplx> buffer;
		for (int j = 0; j < width; j++)
		{
			cmplx value;
			value.image = 0;
			value.real = _imageNoised[i][j];
			buffer.push_back(value);
		}
		image.push_back(buffer);
	}
	Fourie2D(image, -1);
	_imageSpectreCMPLX = image;
	for (int i = 0; i < height; i++)
	{
		std::vector<double> buffer;
		std::vector<double> bufferLog;
		for (int j = 0; j < width; j++)
		{
			double val = sqrt(image[j][i].image*image[j][i].image + image[j][i].real*image[j][i].real);
			if (val < 0) val = 0;
			buffer.push_back(val);

			double valLog = log10(sqrt(image[j][i].image*image[j][i].image + image[j][i].real*image[j][i].real));
			if (valLog < 0) valLog = 0;
			bufferLog.push_back(valLog);
		}
		_imageSpectre.push_back(buffer);
		_imageSpectreLog.push_back(bufferLog);
	}
	NormilizeAmplitude(_imageSpectre, 2, 2);
	NormilizeAmplitude(_imageSpectreLog, 2, 2);
	RelocateSpectre();
	_picture2._ellipseDrawing = false;
	if (_isLog)	_picture2._image = &_imageSpectreLogToDraw;
	else _picture2._image = &_imageSpectreToDraw;
	_picture2.Update();
}

void CFilterDlg::GaussianDistribution()
{
	_image.clear();
	for (int i = 0; i < _heightGauss; i++)
	{
		std::vector<double> bufValues;
		for (int j = 0; j < _widthGauss; j++)
		{
			double value;
			value = (_A1 * exp(-((j - _x1)*(j - _x1) + (i - _y1)*(i - _y1)) / (_sx1*_sx1 + _sy1 * _sy1)) +
				_A2 * exp(-((j - _x2)*(j - _x2) + (i - _y2)*(i - _y2)) / (_sx2*_sx2 + _sy2 * _sy2)) +
				_A3 * exp(-((j - _x3)*(j - _x3) + (i - _y3)*(i - _y3)) / (_sx3*_sx3 + _sy3 * _sy3))) / (_A1 + _A2 + _A3)*255.f;
			bufValues.push_back(value);
		}
		_image.push_back(bufValues);
	}
	_imageNoised = _image;
	AddNoise();
	//AddZeroToPicture(_image);
	//AddZeroToPicture(_imageNoised);
	InterpolateImage(_image);
	InterpolateImage(_imageNoised);
	NormilizeAmplitude(_image, 0, 0);
	NormilizeAmplitude(_imageNoised, 0, 0);
	InitializeSlider();
}

void CFilterDlg::OnBnClickedGauss()
{
	UpdateData(TRUE);
	GaussianDistribution();
	if (_radioOriginal == 0) OnBnClickedRadioOrig();
	else OnBnClickedRadioN();
}

void CFilterDlg::EnergySelecter()
{
	double height = _imageSpectreCMPLX.size(),
		width = _imageSpectreCMPLX[0].size();
	double energyFull = 0, selectedEnergy = 0;


#pragma omp parallel for reduction(+:energyFull)
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			energyFull += _imageSpectreCMPLX[i][j].real*_imageSpectreCMPLX[i][j].real +
				_imageSpectreCMPLX[i][j].image*_imageSpectreCMPLX[i][j].image;
		}
	}

#pragma omp parallel for reduction(+:selectedEnergy)
	for (int i = 0; i <= height / 2; i++)
	{
		for (int j = 0; j <= width / 2; j++)
		{
			if (_isBatterworth)
			{
				selectedEnergy += _imageSpectreCMPLX[i][j].image*_imageSpectreCMPLX[i][j].image +
					_imageSpectreCMPLX[i][j].real*_imageSpectreCMPLX[i][j].real;
				_imageSpectreCMPLX[i][j].image *= (double)(1.0 / (1.0 + sqrt(i*i + j * j) / (double)_R*
					sqrt(i*i + j * j) / (double)_R));
				_imageSpectreCMPLX[i][j].real *= (double)(1.0 / (1.0 + sqrt(i*i + j * j) / (double)_R*
					sqrt(i*i + j * j) / (double)_R));
			}
			else
			{
				if (sqrt(i*i + j * j) >= (double)_R)
				{
					_imageSpectreCMPLX[i][j].image = 0;
					_imageSpectreCMPLX[i][j].real = 0;
				}
				else
				{
					selectedEnergy += _imageSpectreCMPLX[i][j].image*_imageSpectreCMPLX[i][j].image +
						_imageSpectreCMPLX[i][j].real*_imageSpectreCMPLX[i][j].real;
				}
			}
		}
	}
#pragma omp parallel for reduction(+:selectedEnergy)
	for (int i = 0; i <= height / 2; i++)
	{
		for (int j = width - 1; j >= width / 2; j--)
		{
			if (_isBatterworth)
			{
				selectedEnergy += _imageSpectreCMPLX[i][j].image*_imageSpectreCMPLX[i][j].image +
					_imageSpectreCMPLX[i][j].real*_imageSpectreCMPLX[i][j].real;
				_imageSpectreCMPLX[i][j].image *= (double)(1.0 / (1.0 + sqrt(i*i + (width - 1 - j) *(width - 1 - j))
					/ (double)_R*sqrt(i*i + (width - 1 - j) *(width - 1 - j)) / (double)_R));
				_imageSpectreCMPLX[i][j].real *= (double)(1.0 / (1.0 + sqrt(i*i + (width - 1 - j) *(width - 1 - j))
					/ (double)_R*sqrt(i*i + (width - 1 - j) *(width - 1 - j)) / (double)_R));
			}
			else
			{
				if (sqrt(i*i + (width - 1 - j) *(width - 1 - j)) >= (double)_R)
				{
					_imageSpectreCMPLX[i][j].image = 0;
					_imageSpectreCMPLX[i][j].real = 0;
				}
				else
				{
					selectedEnergy += _imageSpectreCMPLX[i][j].image*_imageSpectreCMPLX[i][j].image +
						_imageSpectreCMPLX[i][j].real*_imageSpectreCMPLX[i][j].real;
				}
			}

		}
	}
#pragma omp parallel  for reduction(+:selectedEnergy)
	for (int i = height - 1; i >= height / 2; i--)
	{
		for (int j = 0; j <= width / 2; j++)
		{
			if (_isBatterworth)
			{
				selectedEnergy += _imageSpectreCMPLX[i][j].image*_imageSpectreCMPLX[i][j].image +
					_imageSpectreCMPLX[i][j].real*_imageSpectreCMPLX[i][j].real;
				_imageSpectreCMPLX[i][j].image *= (double)(1.0 / (1.0 + sqrt((height - 1 - i)*(height - 1 - i) + j * j)
					/ (double)_R*sqrt((height - 1 - i)*(height - 1 - i) + j * j) / (double)_R));
				_imageSpectreCMPLX[i][j].real *= (double)(1.0 / (1.0 + sqrt((height - 1 - i)*(height - 1 - i) + j * j)
					/ (double)_R*sqrt((height - 1 - i)*(height - 1 - i) + j * j) / (double)_R));
			}
			else
			{
				if (sqrt((height - 1 - i)*(height - 1 - i) + j * j) >= (double)_R)
				{
					_imageSpectreCMPLX[i][j].image = 0;
					_imageSpectreCMPLX[i][j].real = 0;
				}
				else
				{
					selectedEnergy += _imageSpectreCMPLX[i][j].image*_imageSpectreCMPLX[i][j].image +
						_imageSpectreCMPLX[i][j].real*_imageSpectreCMPLX[i][j].real;
				}
			}
		}
	}

#pragma omp parallel  for reduction(+:selectedEnergy)
	for (int i = height - 1; i >= height / 2; i--)
	{
		for (int j = width - 1; j >= width / 2; j--)
		{
			if (_isBatterworth)
			{
				selectedEnergy += _imageSpectreCMPLX[i][j].image*_imageSpectreCMPLX[i][j].image +
					_imageSpectreCMPLX[i][j].real*_imageSpectreCMPLX[i][j].real;
				_imageSpectreCMPLX[i][j].image *= (double)(1.0 / (1.0 + sqrt((height - 1 - i)*(height - 1 - i) + (width - 1 - j) * (width - 1 - j))
					/ (double)_R*sqrt((height - 1 - i)*(height - 1 - i) + (width - 1 - j) * (width - 1 - j))
					/ (double)_R));
				_imageSpectreCMPLX[i][j].real *= (double)(1.0 / (1.0 + sqrt((height - 1 - i)*(height - 1 - i) + (width - 1 - j) * (width - 1 - j))
					/ (double)_R*sqrt((height - 1 - i)*(height - 1 - i) + (width - 1 - j) * (width - 1 - j))
					/ (double)_R));
			}
			else
			{
				if (sqrt((height - 1 - i)*(height - 1 - i) + (width - 1 - j) * (width - 1 - j)) >= (double)_R)
				{
					_imageSpectreCMPLX[i][j].image = 0;
					_imageSpectreCMPLX[i][j].real = 0;
				}
				else
				{
					selectedEnergy += _imageSpectreCMPLX[i][j].image*_imageSpectreCMPLX[i][j].image +
						_imageSpectreCMPLX[i][j].real*_imageSpectreCMPLX[i][j].real;
				}
			}
		}
	}
	CString str;
	float val = selectedEnergy / energyFull;
	str.Format(TEXT("%.4f"), val);
	_threshholdEnergyText.SetWindowTextW(str);

	_imageSpectre.clear();
	_imageSpectreLog.clear();
	for (int i = 0; i < height; i++)
	{
		std::vector<double> buffer;
		std::vector<double> bufferLog;
		for (int j = 0; j < width; j++)
		{
			double val = sqrt(_imageSpectreCMPLX[j][i].image*_imageSpectreCMPLX[j][i].image
				+ _imageSpectreCMPLX[j][i].real*_imageSpectreCMPLX[j][i].real);
			if (val < 0) val = 0;

			double valLog = log(sqrt(_imageSpectreCMPLX[j][i].image*_imageSpectreCMPLX[j][i].image
				+ _imageSpectreCMPLX[j][i].real*_imageSpectreCMPLX[j][i].real));
			if (valLog < 0) valLog = 0;
			buffer.push_back(val);
			bufferLog.push_back(valLog);
		}
		_imageSpectre.push_back(buffer);
		_imageSpectreLog.push_back(bufferLog);
	}
	NormilizeAmplitude(_imageSpectre, 2, 2);
	NormilizeAmplitude(_imageSpectreLog, 2, 2);
	RelocateSpectre();
}

void CFilterDlg::OnBnClickedEnergy()
{
	UpdateData(TRUE);
	EnergySelecter();
	_picture2._ellipseDrawing = false;
	_picture2.Update();
}


void CFilterDlg::OnBnClickedToimage()
{
	Fourie2D(_imageSpectreCMPLX, 1);
	double height = _imageSpectreCMPLX.size(),
		width = _imageSpectreCMPLX[0].size();
	_imageSpectre.clear();
	for (int i = 0; i < height; i++)
	{
		std::vector<double> buffer;
		for (int j = 0; j < width; j++)
		{
			double value = _imageSpectreCMPLX[i][j].real;
			if (value < 0) value = 0;
			buffer.push_back(value);
		}
		_imageSpectre.push_back(buffer);
	}
	NormilizeAmplitude(_imageSpectre, 0, 0);
	_picture2._image = &_imageSpectre;
	_picture2._ellipseDrawing = false;

	CString str;
	str.Format(_TEXT("%.4f"), SquareDeviation(_image, _imageSpectre));
	_squarenessDevText.SetWindowTextW(str);
	_picture2.Update();
}

void CFilterDlg::NormilizeAmplitude(std::vector<std::vector<double>> &pData, int indentX, int indentY)
{
	double max = 0;

	double height = pData.size(),
		width = pData[0].size();

	//#pragma omp parallel for
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (((j < indentX) && (i < indentY))
				|| (((height - i) < indentY) && ((width - j) < indentX))
				|| (((height - i) < indentY) && (j < indentX))
				|| ((i < indentY) && ((width - j) < indentX)))
				continue;
			if (pData[i][j] > max) max = pData[i][j];
		}
	}
	//#pragma omp parallel for
	int pp = 0;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (((j < indentX) && (i < indentY))
				|| (((height - i) < indentY) && ((width - j) < indentX))
				|| (((height - i) < indentY) && (j < indentX))
				|| ((i < indentY) && ((width - j) < indentX)))
			{
				pData[i][j] = 255.f;
				continue;
			}
			pData[i][j] = pData[i][j] / max * 255.f;
		}
	}
}

void CFilterDlg::InterpolateImage(std::vector<std::vector<double>> &image)
{
	int width = image[0].size(),
		height = image.size(),
		newWidth = 0, newHeight = 0;
	CheckBin(width, newWidth);
	CheckBin(height, newHeight);

	CString str, arg1, arg2;
	str = "Resolution: ";
	arg1.Format(_T("%d"), width);
	arg2.Format(_T("%d"), height);
	str += arg1 + "x" + arg2;
	_dpiText.SetWindowTextW(str);

	CString str2, arg3, arg4;
	str2 = "New resolution: ";
	arg3.Format(_T("%d"), newWidth);
	arg4.Format(_T("%d"), newHeight);
	str2 += arg3 + "x" + arg4;
	_dpiTextNew.SetWindowTextW(str2);

	double stepX = (double)width / (newWidth + 1.0);
	double stepY = (double)height / (newHeight + 1.0);
	std::vector<std::vector<double>> tempData;

	for (int h = 0; h < height; h++)
	{
		std::vector<double> bufLine;
		for (int i = 0; i < newWidth; i++)
		{
			double x = i * stepX;
			for (int w = 1; w < width; w++)
			{
				if ((x >= w - 1) && (x < w))
				{
					double value = (double)(image[h][w] - image[h][w - 1])*x +
						(double)(image[h][w - 1] - (image[h][w] - image[h][w - 1])*((double)w - 1.f));
					bufLine.push_back(value);
				}
			}
		}
		tempData.push_back(bufLine);
	}

	std::vector<std::vector<double>> transponData;
	for (int i = 0; i < newWidth; i++)
	{
		std::vector<double> bufCol;
		for (int j = 0; j < height; j++)
		{
			bufCol.push_back(tempData[j][i]);
		}
		transponData.push_back(bufCol);
	}

	tempData.clear();

	width = transponData[0].size();
	height = transponData.size();

	newWidth = newHeight;
	for (int h = 0; h < height; h++)
	{
		std::vector<double> bufLine;
		for (int i = 0; i < newWidth; i++)
		{
			double x = i * stepY;
			for (int w = 1; w < width; w++)
			{
				if ((x >= w - 1) && (x < w))
				{
					double value = (double)(transponData[h][w] - transponData[h][w - 1])*x +
						(double)(transponData[h][w - 1] - (transponData[h][w] - transponData[h][w - 1])*((double)w - 1.f));
					bufLine.push_back(value);
				}
			}
		}
		tempData.push_back(bufLine);
	}

	transponData.clear();
	for (int i = 0; i < newWidth; i++)
	{
		std::vector<double> bufCol;
		for (int j = 0; j < newHeight; j++)
		{
			bufCol.push_back(tempData[j][i]);
		}
		transponData.push_back(bufCol);
	}

	image = transponData;
}


void CFilterDlg::OnBnClickedRadioOrig()
{
	UpdateData(TRUE);
	_radioOriginal = 0;
	_radioNoised = 1;
	if (!_image.empty())_picture1._image = &_image;
	_picture1.Update();
	UpdateData(FALSE);
}


void CFilterDlg::OnBnClickedRadioN()
{
	UpdateData(TRUE);
	_radioOriginal = 1;
	_radioNoised = 0;
	if (!_imageNoised.empty())_picture1._image = &_imageNoised;
	_picture1.Update();
	UpdateData(FALSE);
}


void CFilterDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	pScrollBar == (CScrollBar *)&_sliderR;
	_picture2._ellipseDrawing = true;
	_R = _sliderR.GetPos();
	_picture2.RedrawWindow();
	CString str, arg;
	str = "Radius: ";
	arg.Format(_T("%d"), _R);
	str += arg;
	_radiusText.SetWindowTextW(str);
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CFilterDlg::InitializeSlider()
{
	_sliderR.SetRange(1, _imageNoised[0].size() / 2);
	_sliderR.SetPos(1);
	_sliderR.SetTicFreq(5);
	_R = _sliderR.GetPos();
	_picture2._R = &_R;
}

void CFilterDlg::RelocateSpectre()
{
	_imageSpectreToDraw = _imageSpectre;
	_imageSpectreLogToDraw = _imageSpectreLog;

	int width = _imageSpectre[0].size(),
		height = _imageSpectre.size();

	for (int i = 0; i < height / 2; i++)
	{
		for (int j = 0; j < width / 2; j++)
		{
			_imageSpectreToDraw[i][j] = _imageSpectre[i + height / 2][j + width / 2];
			_imageSpectreLogToDraw[i][j] = _imageSpectreLog[i + height / 2][j + width / 2];
		}
	}
	for (int i = 0; i < height / 2; i++)
	{
		for (int j = 0; j < width / 2; j++)
		{
			_imageSpectreToDraw[i + height / 2][j + width / 2] = _imageSpectre[i][j];
			_imageSpectreLogToDraw[i + height / 2][j + width / 2] = _imageSpectreLog[i][j];
		}
	}
	for (int i = height / 2 - 1; i >= 0; i--)
	{
		for (int j = width / 2; j < width; j++)
		{
			_imageSpectreToDraw[i][j] = _imageSpectre[i + height / 2][j - width / 2];
			_imageSpectreLogToDraw[i][j] = _imageSpectreLog[i + height / 2][j - width / 2];
		}
	}
	for (int i = height / 2 - 1; i >= 0; i--)
	{
		for (int j = width / 2; j < width; j++)
		{
			_imageSpectreToDraw[i + height / 2][j - width / 2] = _imageSpectre[i][j];
			_imageSpectreLogToDraw[i + height / 2][j - width / 2] = _imageSpectreLog[i][j];
		}
	}
}

double CFilterDlg::SquareDeviation(std::vector<std::vector<double>> pDataOriginal, std::vector<std::vector<double>> pDataResult)
{
	const int width = pDataOriginal[0].size();
	const int height = pDataOriginal.size();
	double original = 0, deviation = 0;
#pragma omp parallel for reduction(+:original,deviation)
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			original += pDataOriginal[i][j] * pDataOriginal[i][j];
			deviation += (pDataOriginal[i][j] - pDataResult[i][j])*(pDataOriginal[i][j] - pDataResult[i][j]);
		}
	}

	return deviation / original;
}

void CFilterDlg::OnBnClickedLog()
{
	UpdateData(TRUE);
	_picture2._ellipseDrawing = false;
	if (_isLog)	_picture2._image = &_imageSpectreLogToDraw;
	else _picture2._image = &_imageSpectreToDraw;
	_picture2.Update();
}


void CFilterDlg::OnBnClickedCheck1()
{
	// TODO: добавьте свой код обработчика уведомлений
}
