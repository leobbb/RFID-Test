// k������˽ģ��

#include "stdafx.h"
using namespace std;


// ģ���ǩ��Ϊ�ĺ���
Response_Info TagFun(Request_Info req){

	cout << endl << "Request_Info: " << req << endl;

	unint quaId, key, r1;
	quaId = req.QuasiId;	// ��ȡ Request_Info�ڵ���Ϣ
	key = req.key;
	r1 = req.r1;

	minstd_rand0 minrand(r1&key);		// �����������ʹ��r1��key�Ĳ���Ϊ����
	unsigned int r2 = minrand();

	cout << endl << "TagFun Start ----" << endl;
	cout << "r1: " << r1 << "\tr2: " << r2 << endl;
	cout << "Key: " << key << endl;

	hash<unsigned int > int_hash;		// ����Hashֵ
	unsigned int h = int_hash(r1&r2&key);
		cout << "hash(r1,r2,key): " << h << endl;

	Response_Info res;			// ������Ӧ��Ϣ
	res.QuasiId = quaId;
	res.r2 = r2;
	res.h = h;
	cout << endl << "Response_Info: " << res << endl;

	return  res;
}

std::ostream& operator<<(ostream & out, Request_Info value){		// ��� ��ѯ��Ϣ
	out << value.QuasiId << " " << value.key << " " << value.r1;
	return out;
}

std::ostream& operator<<(ostream & out, Response_Info value){		// ��� ��Ӧ��Ϣ
	out << value.QuasiId << " " << value.r2 << " " << value.h;
	return out;
}

// ģ���Ķ�����Ϊ�ĺ���
Result_Info ReaderFun(Response_Info res, unint r1){ 
	// ��ȡ��Ӧ��Ϣ
	unint qua, r2, h;
	qua = res.QuasiId;
	r2 = res.r2;
	h = res.h;

	// �������ݿ�
	unint key2 = 12345;		// ���ݿ��д洢�ı�ǩ��key
	hash<unint> int_hash;
	unint h1 = int_hash(r1&r2&key2);

	if (h1 == h)
		return '1';

	return '0';
}