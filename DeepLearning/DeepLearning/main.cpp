#include "Numpy.h"
#include<memory>
#include<iostream>

//class temp
//{
//public:
//	temp(std::unique_ptr<int> a)
//		: mArray(std::move(a))
//	{
//	}
//private:
//	std::unique_ptr<int> mArray;
//};
//
//temp test()
//{
//	std::unique_ptr<int> a = std::make_unique<int>(5);
//
//	return temp(std::move(a));
//}

void test1()
{
	unsigned int arraySize[2];
	arraySize[0] = 4;
	arraySize[1] = 5;
	std::unique_ptr<unsigned int[]> arraySize2 = std::make_unique<unsigned int[]>(2);
	arraySize2[0] = 4;
	arraySize2[1] = 5;
	std::unique_ptr<int[]> array = std::make_unique<int[]>(8);

	numpy::Ndarray<int> array1(2, 20, std::move(arraySize2), std::move(array));

	numpy::Ndarray<int> array2 = numpy::Numpy<int>::Zeros(arraySize);

	numpy::Ndarray<int> array3 = array2;
	assert(array2 == array3);
	std::cout << "N Data Array Make Test Done" << std::endl;

	std::cout << array2 << std::endl;
	arraySize[0] = 2;
	arraySize[1] = 10;
	array2.Reshape(arraySize);
	std::cout << array2 << std::endl;
	arraySize[0] = 10;
	arraySize[1] = 2;
	array2.Reshape(arraySize);
	std::cout << array2 << std::endl;
	arraySize[0] = 5;
	arraySize[1] = 4;
	array2.Reshape(arraySize);
	std::cout << array2 << std::endl;
	std::cout << "N Data Array Reshape Test Done" << std::endl;

	array2 = array2 + array2;
	std::cout << array2 << std::endl;
}

void test2()
{

}

int main()
{
	test1();

	std::cout << "Test Done" << std::endl;
}


//import numpy as np
//# import cupy as np  # GPU�� �̿��� ���
//import matplotlib.pyplot as plt
//from sklearn import datasets
//from sklearn.model_selection import train_test_split
//
//# -- �� ������ --
//img_size = 8  # �̹��� ũ��� ��
//n_mid = 16  # ������ ���� ��
//n_out = 10
//eta = 0.001  # �н���
//epochs = 51
//batch_size = 32
//interval = 5  # ��� �ð� ǥ�� ����
//
//digits_data = datasets.load_digits()
//
//# -- �Է� ������ --
//input_data = np.asarray(digits_data.data)
//input_data = (input_data - np.average(input_data)) / np.std(input_data)  # ���0��ǥ������ 1
//
//# -- ���� ������ --
//correct = np.asarray(digits_data.target)
//correct_data = np.zeros((len(correct), n_out))
//for i in range(len(correct)) :
//    correct_data[i, correct[i]] = 1  # ���� ���ڵ�
//
//# -- �Ʒ� �����Ϳ� �׽�Ʈ �����ͷ� ���� --
//    x_train, x_test, t_train, t_test = train_test_split(input_data, correct_data)
//
//# -- ���������� �θ� Ŭ���� --
//    class BaseLayer :
//    def update(self, eta) :
//    self.w -= eta * self.grad_w
//    self.b -= eta * self.grad_b
//
//# -- ������ --
//    class MiddleLayer(BaseLayer) :
//    def __init__(self, n_upper, n) :
//    self.w = np.random.randn(n_upper, n) * np.sqrt(2 / n_upper)  # He����Ѣ��
//    self.b = np.zeros(n)
//
//    def forward(self, x) :
//    self.x = x
//    self.u = np.dot(x, self.w) + self.b
//    self.y = np.where(self.u <= 0, 0, self.u) # ReLU
//
//    def backward(self, grad_y) :
//    delta = grad_y * np.where(self.u <= 0, 0, 1)  # ReLU �̺�
//
//    self.grad_w = np.dot(self.x.T, delta)
//    self.grad_b = np.sum(delta, axis = 0)
//    self.grad_x = np.dot(delta, self.w.T)
//
//# -- ����� --
//    class OutputLayer(BaseLayer) :
//    def __init__(self, n_upper, n) :
//    self.w = np.random.randn(n_upper, n) / np.sqrt(n_upper)  # �ں񿡸� �ʱ�ȭ ����� �ʱ갪
//    self.b = np.zeros(n)
//
//    def forward(self, x) :
//    self.x = x
//    u = np.dot(x, self.w) + self.b
//    self.y = np.exp(u) / np.sum(np.exp(u), axis = 1, keepdims = True)  # ����Ʈ�ƽ� �Լ�
//
//    def backward(self, t) :
//    delta = self.y - t
//
//    self.grad_w = np.dot(self.x.T, delta)
//    self.grad_b = np.sum(delta, axis = 0)
//    self.grad_x = np.dot(delta, self.w.T)
//
//# -- ������ �ʱ�ȭ --
//    layers = [MiddleLayer(img_size * img_size, n_mid),
//    MiddleLayer(n_mid, n_mid),
//    OutputLayer(n_mid, n_out)]
//
//# -- ������ --
//    def forward_propagation(x) :
//    for layer in layers :
//layer.forward(x)
//x = layer.y
//return x
//
//# -- ������ --
//def backpropagation(t) :
//    grad_y = t
//    for layer in reversed(layers) :
//        layer.backward(grad_y)
//        grad_y = layer.grad_x
//        return grad_y
//
//# -- �Ķ���� ���� --
//        def update_params() :
//        for layer in layers :
//layer.update(eta)
//
//# -- ���� ���� --
//def get_error(x, t) :
//    y = forward_propagation(x)
//    return -np.sum(t * np.log(y + 1e-7)) / len(y)  # ������Ʈ���� ����
//
//# -- ����� ���� --
//    def get_accuracy(x, t) :
//    y = forward_propagation(x)
//    count = np.sum(np.argmax(y, axis = 1) == np.argmax(t, axis = 1))
//    return count / len(y)
//
//# -- ���� ��� --
//    error_record_train = []
//    error_record_test = []
//
//    n_batch = len(x_train) // batch_size  # 1����ũ�� ��ġ ����
//    for i in range(epochs) :
//
//# -- �н� -- 
//        index_random = np.arange(len(x_train))
//        np.random.shuffle(index_random)  # �ε��� ���� ����
//        for j in range(n_batch) :
//
//            # �̴Ϲ�ġ ����
//            mb_index = index_random[j * batch_size:(j + 1) * batch_size]
//            x_mb = x_train[mb_index, :]
//            t_mb = t_train[mb_index, :]
//
//            # �����Ŀ� ������
//            forward_propagation(x_mb)
//            backpropagation(t_mb)
//
//            # �Ķ���� ����
//            update_params()
//
//# -- ���� ���� �� ��� --  
//            error_train = get_error(x_train, t_train)
//            error_record_train.append(error_train)
//            error_test = get_error(x_test, t_test)
//            error_record_test.append(error_test)
//
//# -- ��� ǥ�� -- 
//            if i% interval == 0:
//print("Epoch:" + str(i + 1) + "/" + str(epochs),
//    "Error_train: " + str(error_train),
//    "Error_test: " + str(error_test))
//
//# -- ���� ���̸� �׷����� ǥ�� - -- 
//    plt.plot(range(1, len(error_record_train) + 1), error_record_train, label = "Train")
//    plt.plot(range(1, len(error_record_test) + 1), error_record_test, label = "Test")
//    plt.legend()
//
//    plt.xlabel("Epochs")
//    plt.ylabel("Error")
//    plt.show()
//
//# -- - ����� ���� -- 
//    acc_train = get_accuracy(x_train, t_train)
//    acc_test = get_accuracy(x_test, t_test)
//
//    print("Acc_train: " + str(acc_train * 100) + "%", "Acc_test: " + str(acc_test * 100) + "%")