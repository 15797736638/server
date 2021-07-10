/**
    Thread.h
*/
#ifdef WIN32
typedef HANDLE THREAD_HANDLE;
#else
typedef pthread_t THREAD_HANDLE;
#endif

/**
 * 定义一个线程对象
 */

/**
 * 定义一个线程对象
 */
class CThread{
public:
    CThread();
    virtual ~CThread();

    /**
     * 创建一个线程
     * @return true:创建成功：false：创建失败
     */
    virtual bool Create();
    
    /**获得本线程对象存储的线程句柄
     * @return本线程对象存储的线程句柄
     */
    
    THREAD_HANDLE GetHandle();
    
    /**线程睡眠 nSeconds 秒
     * @parm nSeconds，睡眠秒数
     */
    void OSSleep(int nSeconds);
    void SleepMs(int nMilliseconds);
    bool Join();
    bool IseCurrentThread();
    void ExitThread();

private:
#ifdef WIN32
    static DWORD WINAPI _ThreadEntry(LPVOID pParam);
#else
    static void* _ThreadEntry(void* pParam);
#endif 
    
    /**虚函数，子类可做一些实例化工作
     * @return true:创建成功 false:创建失败
     */
    virtual bool InitInstance();

    /**虚函数，子类清除实例
     */
    virtual void ExitInstance();

    /**存放线程函数的实际业务逻辑，纯虚函数，子类必须重写该函数
     */
    virtual void Run() = 0;

private:
    //线程句柄
    THREAD_HANDLE m_hThread;
    DWORD m_IDThread;
}
