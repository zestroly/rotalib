#ifndef BARCODESCANNER_H
#define BARCODESCANNER_H



class BarCodeScanner
{
public:
    BarCodeScanner();
    ~BarCodeScanner();
    bool openDev();
    bool closeDev();

    void Scanne();


private:
    int m_fd;
    bool m_available;
};

#endif // BARCODESCANNER_H
