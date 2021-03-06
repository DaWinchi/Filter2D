// FilterDlg.h: файл заголовка
//

#pragma once

#include "CModelDraw.h"

using namespace Gdiplus;
// Диалоговое окно CFilterDlg
class CFilterDlg : public CDialogEx
{
	// Создание
public:
	CFilterDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FILTER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
protected:
	struct cmplx { float real; float image; };
public:
	CModelDraw _picture1;
	std::vector<std::vector<double>> _image;
	std::vector<std::vector<double>> _imageNoised;
	std::vector<std::vector<double>> _imageSpectre;
	std::vector<std::vector<double>> _imageSpectreLog;
	std::vector<std::vector<double>> _imageSpectreToDraw;
	std::vector<std::vector<double>> _imageSpectreLogToDraw;
	std::vector<std::vector<cmplx>> _imageSpectreCMPLX;
	afx_msg void OnBnClickedLoad();
	void LoadPicture();
	bool CheckBin(int value, int &newvalue);
	void AddZeroToPicture(std::vector<std::vector<double>> &image);
	void InterpolateImage(std::vector<std::vector<double>> &image);
	void AddNoise();
	void Fourie1D(std::vector<cmplx> *data, int n, int is);
	void Fourie2D(std::vector<std::vector<cmplx>> &data, int is);
	void GaussianDistribution();
	void EnergySelecter();
	void NormilizeAmplitude(std::vector<std::vector<double>> &pData, int indentX, int indentY);
	CStatic _dpiText;
	CStatic _dpiTextNew;
	double percentNoise;
	afx_msg void OnBnClickedSpectre();
	CModelDraw _picture2;
	double _A1;
	double _A2;
	double _A3;
	double _x1;
	double _y1;
	double _sx1;
	double _sy1;
	double _x2;
	double _y2;
	double _sx2;
	double _sy2;
	double _x3;
	double _y3;
	double _sx3;
	double _sy3;
	int _heightGauss;
	int _widthGauss;
	afx_msg void OnBnClickedGauss();
	afx_msg void OnBnClickedEnergy();
	afx_msg void OnBnClickedToimage();
	afx_msg void OnBnClickedRadioOrig();
	afx_msg void OnBnClickedRadioN();
	int _radioOriginal;
	int _radioNoised;
	CSliderCtrl _sliderR;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	void InitializeSlider();
	int _R;
	void RelocateSpectre();
	double SquareDeviation(std::vector<std::vector<double>> pDataOriginal, std::vector<std::vector<double>> pDataResult);
	CStatic _radiusText;
	CStatic _threshholdEnergyText;
	CStatic _squarenessDevText;
	BOOL _isLog;
	afx_msg void OnBnClickedLog();
	CStatic _squarenessDevOrigNoisedText;
	BOOL _isBatterworth;
	afx_msg void OnBnClickedCheck1();
};
