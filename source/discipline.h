#pragma once
#ifndef H_DISCIPLINE_
#define H_DISCIPLINE_
void zeros_data();
void sigmoid_prime(const double s[], double o[], int count);
void sigmoid(const double in[], double out[], int count);
void backprop(train_data* data);
void SGD(int epochs, double eta, int mini_batch_size, train_data train_datas[], int train_data_count);
void update_mini_batch(train_data * ptr_train_data, double eta, int mini_batch_size);
#endif // !H_DISCIPLINE_
