namespace Rice
{
    class Time
    {
    public:
        static void BeginFrame();
    
        static double Seconds() { return m_TimeNow; }
        static double Milliseconds() { return m_TimeNow * 1000.0; }
    
        static double DTSeconds() { return m_DeltaTime; }
        static double DTMilliseconds() { return m_DeltaTime * 1000.0; }
    
    private:
        static double m_TimeNow;
        static double m_DeltaTime;
    };
}
