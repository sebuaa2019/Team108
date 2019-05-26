int nNumObj = vObj.size();

if(nNumObj = vObj.size())
{
	stBoxMarker Temp;
	for(int i = 0; i < nNumObj; i++){
		for(int j = 0; j < nNumObj - i; j++){
			float fMidY_now = (vObj[j].yMin + vObj[j].yMax)/2;
			float fMidY_next = (vObj[j+1].yMin + vObj[j+1].yMax)/2;
			if(fMidY_now > fMidY_next){
				Temp = vObj[j];
				vObj[j] = vObj[j+1];
				vObj[j+1] = Temp;
			}
		}
	}
}

//后续输入选择物体即可