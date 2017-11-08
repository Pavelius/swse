#include "main.h"

bool creature::is(feat_s id) const
{
	return (feats[id / 8] & (1 << (id % 8)))!=0;
}

void creature::set(feat_s id, bool value)
{
	if(value)
		feats[id / 8] |= (1 << (id % 8));
	else
		feats[id / 8] &= ~(1 << (id % 8));
}