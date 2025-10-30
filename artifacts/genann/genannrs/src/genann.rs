use crate::*;

// typedef struct genann
// {
//   int inputs;
//   int hidden_layers;
//   int hidden;
//   int outputs;
//   genann_actfun activation_hidden;
//   genann_actfun activation_output;
//   int total_weights;
//   int total_neurons;
//   double *weight;
//   double *output;
//   double *delta;
// } genann

pub fn genann_randomize(/* genann *ann */) {
	todo!();
}
pub fn genann_copy(/* const genann *ann */) {
	todo!();
}
pub fn genann_free(/* genann *ann */) {
	todo!();
}
pub fn genann_write(/* const genann *ann, FILE *out */) {
	todo!();
}
pub fn genann_act_sigmoid(/* const genann *ann, double a */) {
	todo!();
}
pub fn genann_act_threshold(/* const struct genann *ann, double a */) {
	todo!();
}
pub fn genann_act_linear(/* const struct genann *ann, double a */) {
	todo!();
}
pub fn genann_act_hidden_indirect(/* const struct genann *ann, double a */) {
	todo!();
}
pub fn genann_act_output_indirect(/* const struct genann *ann, double a */) {
	todo!();
}
pub fn helper_genann_train_1(/* int * const j_ref, int * const k_ref, const genann * const ann, double learning_rate, int h */) {
	todo!();
}
pub fn helper_genann_train_2(/* int * const j_ref, int * const k_ref, const genann * const ann, double learning_rate */) {
	todo!();
}
pub fn helper_genann_train_3(/* int * const j_ref, int * const k_ref, const genann * const ann, int h */) {
	todo!();
}
pub fn helper_genann_run_1(/* unsigned int * const w_idx_ref, int * const k_ref, const genann * const ann, const double * const w, double * const o, const double * const i, unsigned int i_idx */) {
	todo!();
}
pub fn helper_genann_run_2(/* unsigned int * const w_idx_ref, int * const k_ref, const genann * const ann, const double * const w, double * const o, const double * const i, unsigned int i_idx */) {
	todo!();
}
pub fn helper_genann_run_3(/* unsigned int * const w_idx_ref, unsigned int * const i_idx_ref, int * const j_ref, int * const k_ref, const genann * const ann, const double * const w, double * const o, const double * const i */) {
	todo!();
}
pub fn helper_genann_run_4(/* unsigned int * const w_idx_ref, int * const j_ref, int * const k_ref, const genann * const ann, const double * const w, double * const o, const double * const i, unsigned int i_idx */) {
	todo!();
}
pub fn genann_run(/* const genann *ann, const double *inputs */) {
	todo!();
}
pub fn genann_act_sigmoid_cached(/* const genann *ann, double a */) {
	todo!();
}
pub fn genann_init_sigmoid_lookup(/* const genann *ann */) {
	todo!();
}
pub fn genann_init(/* int inputs, int hidden_layers, int hidden, int outputs */) {
	todo!();
}
pub fn helper_genann_train_4(/* int * const j_ref, const genann * const ann, const double * const desired_outputs */) {
	todo!();
}
pub fn genann_train(/* const genann *ann, const double *inputs, const double *desired_outputs, double learning_rate */) {
	todo!();
}
pub fn genann_read(/* FILE *in */) {
	todo!();
}
