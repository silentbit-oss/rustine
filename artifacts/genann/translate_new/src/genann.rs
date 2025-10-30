use crate::*;
use lazy_static::lazy_static;
use rand::Rng;
use std::assert;
use std::f64::consts::E;
use std::f64;
use std::io::Read;
use std::io::Write;
use std::io;
use std::mem;
use std::str::FromStr;
use std::sync::Mutex;

#[derive(Clone)]
pub enum GenannActFun {
    Sigmoid,
    Linear,
    Threshold,
    SymmetricSigmoid,
    Gaussian,
}

#[derive(Clone)]
pub struct Genann {
    pub inputs: i32,
    pub hidden_layers: i32,
    pub hidden: i32,
    pub outputs: i32,
    pub activation_hidden: GenannActFun,
    pub activation_output: GenannActFun,
    pub total_weights: i32,
    pub total_neurons: i32,
    pub weight: Option<Vec<f64>>,
    pub output: Option<Vec<f64>>,
    pub delta: Option<Vec<f64>>,
}


pub fn genann_randomize(ann: &mut Genann) {
    if let Some(weights) = ann.weight.as_mut() {
        let mut rng = rand::thread_rng();
        for i in 0..ann.total_weights as usize {
            let r: f64 = rng.gen(); // generates random f64 between 0.0 and 1.0
            weights[i] = r - 0.5;
        }
    }
}

pub fn genann_copy(ann: &Genann) -> Option<Genann> {
    // Calculate the total size needed for weights, outputs, and deltas
    let total_elements = (ann.total_weights + ann.total_neurons + (ann.total_neurons - ann.inputs)) as usize;
    
    // Create a new Genann with copied fields
    let mut ret = Genann {
        inputs: ann.inputs,
        hidden_layers: ann.hidden_layers,
        hidden: ann.hidden,
        outputs: ann.outputs,
        activation_hidden: ann.activation_hidden.clone(),
        activation_output: ann.activation_output.clone(),
        total_weights: ann.total_weights,
        total_neurons: ann.total_neurons,
        weight: None,
        output: None,
        delta: None,
    };

    // Clone the weight, output, and delta vectors if they exist
    if let Some(weights) = &ann.weight {
        let mut new_weights = weights.clone();
        let mut new_outputs = Vec::with_capacity(ann.total_neurons as usize);
        let mut new_deltas = Vec::with_capacity((ann.total_neurons - ann.inputs) as usize);

        // Copy weights
        ret.weight = Some(new_weights);

        // Initialize output and delta vectors
        if let Some(outputs) = &ann.output {
            new_outputs = outputs.clone();
        }
        ret.output = Some(new_outputs);

        if let Some(deltas) = &ann.delta {
            new_deltas = deltas.clone();
        }
        ret.delta = Some(new_deltas);
    }

    Some(ret)
}
pub fn genann_free(ann: Option<Box<Genann>>) {
    // In Rust, the Box will be automatically dropped when it goes out of scope,
    // so no explicit free is needed. The Option wrapper allows for NULL-equivalent behavior.
    // Just let the Box drop naturally by doing nothing here.
}

pub fn genann_write(ann: &Genann, out: &mut dyn Write) -> std::io::Result<()> {
    write!(
        out,
        "{} {} {} {}",
        ann.inputs, ann.hidden_layers, ann.hidden, ann.outputs
    )?;

    if let Some(weights) = &ann.weight {
        for weight in weights {
            write!(out, " {:.20e}", weight)?;
        }
    }

    Ok(())
}

pub fn genann_act_sigmoid(ann: &Genann, a: f64) -> f64 {
    if a < -45.0 {
        0.0
    } else if a > 45.0 {
        1.0
    } else {
        1.0 / (1.0 + E.powf(-a))
    }
}
pub fn genann_act_threshold(ann: &Genann, a: f64) -> f64 {
    if a > 0.0 {
        1.0
    } else {
        0.0
    }
}
pub fn genann_act_linear(ann: &Genann, a: f64) -> f64 {
    a
}
pub fn genann_act_hidden_indirect(ann: &Genann, a: f64) -> f64 {
    match ann.activation_hidden {
        GenannActFun::Sigmoid => sigmoid(ann, a),
        GenannActFun::Linear => linear(ann, a),
        GenannActFun::Threshold => threshold(ann, a),
        GenannActFun::SymmetricSigmoid => symmetric_sigmoid(ann, a),
        GenannActFun::Gaussian => gaussian(ann, a),
    }
}

// Helper functions for each activation type
fn sigmoid(_ann: &Genann, a: f64) -> f64 {
    1.0 / (1.0 + (-a).exp())
}

fn linear(_ann: &Genann, a: f64) -> f64 {
    a
}

fn threshold(_ann: &Genann, a: f64) -> f64 {
    if a > 0.0 { 1.0 } else { 0.0 }
}

fn symmetric_sigmoid(_ann: &Genann, a: f64) -> f64 {
    -1.0 + 2.0 / (1.0 + (-a).exp())
}

fn gaussian(_ann: &Genann, a: f64) -> f64 {
    (-a * a).exp()
}
pub fn genann_act_output_indirect(ann: &Genann, a: f64) -> f64 {
    match ann.activation_output {
        GenannActFun::Sigmoid => genann_act_sigmoid(ann, a),
        GenannActFun::Linear => genann_act_linear(ann, a),
        GenannActFun::Threshold => genann_act_threshold(ann, a),
        GenannActFun::SymmetricSigmoid => 2.0 * genann_act_sigmoid(ann, a) - 1.0,
        GenannActFun::Gaussian => (-a * a).exp(),
    }
}

pub fn genann_init_sigmoid_lookup(ann: &Genann) {
    let f = (SIGMOID_DOM_MAX - SIGMOID_DOM_MIN) / 4096.0;
    unsafe {
        interval = 4096.0 / (SIGMOID_DOM_MAX - SIGMOID_DOM_MIN);
    }
    
    let mut lookup = LOOKUP.lock().unwrap();
    for i in 0..4096 {
        lookup[i] = genann_act_sigmoid(ann, SIGMOID_DOM_MIN + (f * i as f64));
    }
}

pub fn genann_act_sigmoid_cached(ann: &Genann, a: f64) -> f64 {
    assert!(!a.is_nan(), "Input must not be NaN");
    
    if a < SIGMOID_DOM_MIN {
        return LOOKUP.lock().unwrap()[0];
    }
    if a >= SIGMOID_DOM_MAX {
        return LOOKUP.lock().unwrap()[4096 - 1];
    }
    
    let j = ((a - SIGMOID_DOM_MIN) * unsafe { interval } + 0.5) as usize;
    if j >= 4096 {
        return LOOKUP.lock().unwrap()[4096 - 1];
    }
    
    LOOKUP.lock().unwrap()[j]
}

pub fn genann_init(
    inputs: i32,
    hidden_layers: i32,
    hidden: i32,
    outputs: i32,
) -> Option<Genann> {
    // Validate input parameters
    if hidden_layers < 0 {
        return None;
    }
    if inputs < 1 {
        return None;
    }
    if outputs < 1 {
        return None;
    }
    if hidden_layers > 0 && hidden < 1 {
        return None;
    }

    // Calculate weights and neurons
    let hidden_weights = if hidden_layers > 0 {
        ((inputs + 1) * hidden) + ((hidden_layers - 1) * (hidden + 1) * hidden)
    } else {
        0
    };
    let output_weights = (if hidden_layers > 0 { hidden + 1 } else { inputs + 1 }) * outputs;
    let total_weights = hidden_weights + output_weights;
    let total_neurons = inputs + (hidden * hidden_layers) + outputs;

    // Create vectors for weight, output, and delta
    let weight = vec![0.0; total_weights as usize];
    let output = vec![0.0; total_neurons as usize];
    let delta = vec![0.0; (total_neurons - inputs) as usize];

    // Create and initialize the Genann struct
    let mut ret = Genann {
        inputs,
        hidden_layers,
        hidden,
        outputs,
        activation_hidden: GenannActFun::Sigmoid,
        activation_output: GenannActFun::Sigmoid,
        total_weights,
        total_neurons,
        weight: Some(weight),
        output: Some(output),
        delta: Some(delta),
    };

    // Initialize the network
    genann_randomize(&mut ret);
    genann_init_sigmoid_lookup(&ret);

    Some(ret)
}

pub fn genann_read(in_stream: &mut dyn Read) -> Option<Genann> {
    let mut buffer = String::new();
    if in_stream.read_to_string(&mut buffer).is_err() {
        eprintln!("Failed to read input stream");
        return None;
    }

    let mut parts = buffer.split_whitespace();
    
    // Parse the first four integers (inputs, hidden_layers, hidden, outputs)
    let inputs = i32::from_str(parts.next()?).ok()?;
    let hidden_layers = i32::from_str(parts.next()?).ok()?;
    let hidden = i32::from_str(parts.next()?).ok()?;
    let outputs = i32::from_str(parts.next()?).ok()?;

    // Initialize the neural network
    let mut ann = genann_init(inputs, hidden_layers, hidden, outputs)?;

    // Parse weights
    if let Some(weight_vec) = &mut ann.weight {
        for i in 0..ann.total_weights {
            if let Some(weight_str) = parts.next() {
                if let Ok(weight) = f64::from_str(weight_str) {
                    weight_vec[i as usize] = weight;
                } else {
                    eprintln!("Failed to parse weight");
                    return None;
                }
            } else {
                eprintln!("Insufficient weights in input");
                return None;
            }
        }
    } else {
        eprintln!("Weight vector not initialized");
        return None;
    }

    Some(ann)
}
pub fn genann_run<'a>(ann: &'a mut Genann, inputs: &[f64]) -> Option<&'a [f64]> {
    // Get activation functions before any borrows
    let act_hidden = genann_act_hidden_indirect;
    let act_output = genann_act_output_indirect;
    
    // Get activation function types by reference to avoid moving
    let activation_hidden = &ann.activation_hidden;
    let activation_output = &ann.activation_output;

    // Check if required fields are present
    let w = ann.weight.as_ref()?;
    let output = ann.output.as_mut()?;
    
    // Initialize indices and pointers
    let mut w_idx = 0;
    let mut o_idx = ann.inputs as usize;
    let mut i_idx = 0;
    
    // Copy inputs to the beginning of output buffer
    {
        let output_slice = &mut output[..ann.inputs as usize];
        output_slice.copy_from_slice(inputs);
    }
    
    // Create a temporary Genann struct for activation functions
    let temp_ann = Genann {
        activation_hidden: activation_hidden.clone(),
        activation_output: activation_output.clone(),
        inputs: ann.inputs,
        hidden_layers: ann.hidden_layers,
        hidden: ann.hidden,
        outputs: ann.outputs,
        total_weights: ann.total_weights,
        total_neurons: ann.total_neurons,
        weight: None,
        output: None,
        delta: None,
    };

    // Process the case with no hidden layers
    if ann.hidden_layers == 0 {
        let (left, right) = output.split_at_mut(o_idx);
        let ret = &mut right[..ann.outputs as usize];
        
        for j in 0..ann.outputs as usize {
            let mut sum = w[w_idx] * -1.0;
            w_idx += 1;
            
            for k in 0..ann.inputs as usize {
                sum += w[w_idx] * left[k + i_idx];
                w_idx += 1;
            }
            
            ret[j] = act_output(&temp_ann, sum);
        }
        
        return Some(ret);
    }
    
    // Process first hidden layer
    for _ in 0..ann.hidden {
        let mut sum = w[w_idx] * -1.0;
        w_idx += 1;
        
        for k in 0..ann.inputs as usize {
            sum += w[w_idx] * output[k + i_idx];
            w_idx += 1;
        }
        
        output[o_idx] = act_hidden(&temp_ann, sum);
        o_idx += 1;
    }
    
    i_idx += ann.inputs as usize;
    
    // Process remaining hidden layers
    for _ in 1..ann.hidden_layers {
        for _ in 0..ann.hidden {
            let mut sum = w[w_idx] * -1.0;
            w_idx += 1;
            
            for k in 0..ann.hidden as usize {
                sum += w[w_idx] * output[k + i_idx];
                w_idx += 1;
            }
            
            output[o_idx] = act_hidden(&temp_ann, sum);
            o_idx += 1;
        }
        
        i_idx += ann.hidden as usize;
    }
    
    // Process output layer
    let (left, right) = output.split_at_mut(o_idx);
    let ret = &mut right[..ann.outputs as usize];
    for j in 0..ann.outputs as usize {
        let mut sum = w[w_idx] * -1.0;
        w_idx += 1;
        
        for k in 0..ann.hidden as usize {
            sum += w[w_idx] * left[k + i_idx];
            w_idx += 1;
        }
        
        ret[j] = act_output(&temp_ann, sum);
    }
    
    // Verify assertions
    assert!((w_idx as i32) == ann.total_weights);
    assert!((o_idx as i32 + ann.outputs) == ann.total_neurons);
    
    Some(ret)
}
pub fn genann_train(ann: &mut Genann, inputs: &[f64], desired_outputs: &[f64], learning_rate: f64) {
    // Run the network first
    genann_run(ann, inputs);

    // Calculate output layer deltas
    {
        let o = ann.output.as_ref().expect("output not initialized");
        let d = ann.delta.as_mut().expect("delta not initialized");
        let t = desired_outputs;

        let o_start = (ann.inputs + (ann.hidden * ann.hidden_layers)) as usize;
        let o_slice = &o[o_start..o_start + ann.outputs as usize];
        
        let d_start = (ann.hidden * ann.hidden_layers) as usize;
        let d_slice = &mut d[d_start..d_start + ann.outputs as usize];

        if let GenannActFun::Linear = ann.activation_output {
            for j in 0..ann.outputs as usize {
                d_slice[j] = t[j] - o_slice[j];
            }
        } else {
            for j in 0..ann.outputs as usize {
                let o_val = o_slice[j];
                d_slice[j] = (t[j] - o_val) * o_val * (1.0 - o_val);
            }
        }
    }

    // Calculate hidden layer deltas
    for h in (0..ann.hidden_layers).rev() {
        let o = ann.output.as_ref().expect("output not initialized");
        let (d_front, d_back) = ann.delta.as_mut().expect("delta not initialized").split_at_mut(((h + 1) * ann.hidden) as usize);
        let d_slice = &mut d_front[(h * ann.hidden) as usize..];
        let dd_slice = &d_back[..if h == ann.hidden_layers - 1 { 
            ann.outputs as usize 
        } else { 
            ann.hidden as usize 
        }];

        let weights = ann.weight.as_ref().expect("weights not initialized");
        let o_slice = &o[(ann.inputs + (h * ann.hidden)) as usize..(ann.inputs + (h * ann.hidden) + ann.hidden) as usize];
        
        let ww_start = ((ann.inputs + 1) * ann.hidden + ((ann.hidden + 1) * ann.hidden) * h) as usize;
        
        for j in 0..ann.hidden as usize {
            let mut delta = 0.0;
            let k_count = if h == ann.hidden_layers - 1 { 
                ann.outputs 
            } else { 
                ann.hidden 
            };

            for k in 0..k_count as usize {
                let forward_delta = dd_slice[k];
                let windex = (k * (ann.hidden as usize + 1)) + (j + 1);
                let forward_weight = weights[ww_start + windex];
                delta += forward_delta * forward_weight;
            }

            let o_val = o_slice[j];
            d_slice[j] = o_val * (1.0 - o_val) * delta;
        }
    }

    // Update weights for output layer
    {
        let d = ann.delta.as_ref().expect("delta not initialized");
        let w = ann.weight.as_mut().expect("weights not initialized");
        let o = ann.output.as_ref().expect("output not initialized");

        let d_start = (ann.hidden * ann.hidden_layers) as usize;
        let d_slice = &d[d_start..d_start + ann.outputs as usize];

        let w_start = if ann.hidden_layers > 0 {
            ((ann.inputs + 1) * ann.hidden + ((ann.hidden + 1) * ann.hidden) * (ann.hidden_layers - 1)) as usize
        } else {
            0
        };
        let w_slice = &mut w[w_start..];

        let i_start = if ann.hidden_layers > 0 {
            (ann.inputs + (ann.hidden * (ann.hidden_layers - 1))) as usize
        } else {
            0
        };
        let i_slice = &o[i_start..];

        let mut w_idx = 0;
        for j in 0..ann.outputs as usize {
            w_slice[w_idx] += d_slice[j] * learning_rate * -1.0;
            w_idx += 1;

            let input_count = if ann.hidden_layers > 0 { 
                ann.hidden 
            } else { 
                ann.inputs 
            };

            for k in 1..(input_count + 1) as usize {
                w_slice[w_idx] += d_slice[j] * learning_rate * i_slice[k - 1];
                w_idx += 1;
            }
        }

        assert!((w_idx + w_start) == ann.total_weights as usize);
    }

    // Update weights for hidden layers
    for h in (0..ann.hidden_layers).rev() {
        let d = ann.delta.as_ref().expect("delta not initialized");
        let w = ann.weight.as_mut().expect("weights not initialized");
        let o = ann.output.as_ref().expect("output not initialized");

        let d_start = (h * ann.hidden) as usize;
        let d_slice = &d[d_start..d_start + ann.hidden as usize];

        let i_start = if h > 0 {
            (ann.inputs + (ann.hidden * (h - 1))) as usize
        } else {
            0
        };
        let i_slice = &o[i_start..];

        let w_start = if h > 0 {
            ((ann.inputs + 1) * ann.hidden + ((ann.hidden + 1) * ann.hidden) * (h - 1)) as usize
        } else {
            0
        };
        let w_slice = &mut w[w_start..];

        let mut w_idx = 0;
        for j in 0..ann.hidden as usize {
            w_slice[w_idx] += d_slice[j] * learning_rate * -1.0;
            w_idx += 1;

            let input_count = if h == 0 { 
                ann.inputs 
            } else { 
                ann.hidden 
            };

            for k in 1..(input_count + 1) as usize {
                w_slice[w_idx] += d_slice[j] * learning_rate * i_slice[k - 1];
                w_idx += 1;
            }
        }
    }
}
