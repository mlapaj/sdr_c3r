class radio
{
public:
	radio ();
	virtual ~radio ();
private:
	long fs = 2500000; // radio sampling rate
	long frequency;
	/* data */
};
