#include "_Layer_CardChan_.h"


_Layer_CardChan_::_Layer_CardChan_(void)
{
}


_Layer_CardChan_::~_Layer_CardChan_(void)
{
}

bool _Layer_CardChan_::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	return true;
}

void _Layer_CardChan_::initAllCard()
{
	for(int i = 0; i < 100; i++)
	{
		CardChan *pCard = CardChan::create();
		pCard->setID(i);
		pCard->setZOrder(i);
		pCard->setVisible(false);
	}
}

void _Layer_CardChan_::resetGame()
{

}

void _Layer_CardChan_::rotateListCard()
{

}

void _Layer_CardChan_::setMyListCard()
{

}