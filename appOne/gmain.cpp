#define _MAT33_TEST

#include"libOne.h"
//�Q�����x�N�g���i�Q�s�P��̍s��Ƃ��čl���邱�Ƃ��ł���j
class VEC {
public:
    float x, y;
    VEC(float x = 0, float y = 0) {
        this->x = x;
        this->y = y;
    }
};
//�R�s�R��̍s��
class MAT33 {
public:
    float _11, _12, _13;
    float _21, _22, _23;
    float _31, _32, _33;
    MAT33(float _11 = 1, float _12 = 0, float _13 = 0,
        float _21 = 0, float _22 = 1, float _23 = 0,
        float _31 = 0, float _32 = 0, float _33 = 1) {
        this->_11 = _11; this->_12 = _12; this->_13 = _13;
        this->_21 = _21; this->_22 = _22; this->_23 = _23;
        this->_31 = _31; this->_32 = _32; this->_33 = _33;
    }
    //�P�ʍs�������
    void identity() {
        _11 = 1; _12 = 0; _13 = 0;
        _21 = 0; _22 = 1; _23 = 0;
        _31 = 0; _32 = 0; _33 = 1;
    }
    //�g��k���s�������
    void scaling(float x, float y) {
        _11 = x; _12 = 0; _13 = 0;
        _21 = 0; _22 = y; _23 = 0;
        _31 = 0; _32 = 0; _33 = 1;
    }
    //��]�s�������
    void rotate(float angle) {
        float c = cos(angle);
        float s = sin(angle);
        _11 = c; _12 =-s; _13 = 0;
        _21 = s; _22 = c; _23 = 0;
        _31 = 0; _32 = 0; _33 = 1;
    }
    //���s�ړ��s�������
    void translate(float x, float y) {
        _11 = 1; _12 = 0; _13 = x;
        _21 = 0; _22 = 1; _23 = y;
        _31 = 0; _32 = 0; _33 = 1;
    }
    //�u�R�s�R��s��v�Ɓu�Q�s�P��s��i�Q�����x�N�g���j�{�P�s�v�̊|���Z
    VEC operator*(const VEC& v) {
        return VEC(
            _11 * v.x + _12 * v.y + _13 * 1,
            _21 * v.x + _22 * v.y + _23 * 1
        );
    }
    //�R�s�R��s��ǂ����̊|���Z
    MAT33 operator*(const MAT33& m) {
        return MAT33(
            //�P�s��
            _11 * m._11 + _12 * m._21 + _13 * m._31,
            _11 * m._12 + _12 * m._22 + _13 * m._32,
            _11 * m._13 + _12 * m._23 + _13 * m._33,
            //�Q�s��
            _21 * m._11 + _22 * m._21 + _23 * m._31,
            _21 * m._12 + _22 * m._22 + _23 * m._32,
            _21 * m._13 + _22 * m._23 + _23 * m._33,
            //�R�s��
            _31 + m._11 + _32 * m._21 + _33 * m._31,
            _31 + m._12 + _32 * m._22 + _33 * m._32,
            _31 + m._13 + _32 * m._23 + _33 * m._33
        );
    }
    //--------------------------------------------------------
    //�œK�����ꂽMAT33���m�̊|���Z
    //--------------------------------------------------------
    void mulTranslate(float x, float y) {
        // |_11 _12 _13|    |1  0  x| �@ |_11  _12  _11x+_12y+_13| 
        // |_21 _22 _23| �~ |0  1  y| �� |_21  _22  _21x+_22y+_23|
        // |  0   0   1|    |0  0  1|    |  0    0              1|
        _13 += _11 * x + _12 * y;
        _23 += _21 * x + _22 * y;
    }
    void mulScaling(float x, float y) {
        // |_11 _12 _13|    |x  0  0| �@ |_11x _12y _13|
        // |_21 _22 _23| �~ |0  y  0| �� |_21x _22y _23|
        // |  0   0   1|    |0  0  1|    |  0    0    1|
        _11 *= x;    _12 *= y;
        _21 *= x;    _22 *= y;
    }
    void mulRotate(float angle) {
        // |_11 _12 _13|    |c -s  0| �@ |_11c+_12s   _11(-s)+_12c   _13|
        // |_21 _22 _23| �~ |s  c  0| �� |_21c+_22s   _21(-s)+_22c   _23|
        // |  0   0   1|    |0  0  1|    |        0             0      1|
        float c = cos(angle);
        float s = sin(angle);
        float tmp;
        //1�s��
        tmp = _11 * c + _12 * s;
        _12 = _11 * -s + _12 * c;
        _11 = tmp;
        //2�s��
        tmp = _21 * c + _22 * s;
        _22 = _21 * -s + _22 * c;
        _21 = tmp;
    }
};

#ifdef _MAT33_TEST
void gmain() {
    window(1000, 1000);
    while (notQuit) {
        clear();
        mathAxis(3.1f, 255);
    }
}
#endif

