use crate::*;
use rand::Rng;
use std::f64::consts::E;
use std::sync::Mutex;
use lazy_static::lazy_static;
use std::io::Read;
use std::io::Write;
use std::assert;
use std::io;

#[derive(Clone)]
pub struct Genann {
    pub inputs: i32,
    pub hidden_layers: i32,
    pub hidden: i32,
    pub outputs: i32,
    pub activation_hidden: Genann_Actfun,
    pub activation_output: Genann_Actfun,
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
            let r: f64 = rng.gen(); // generates random float between 0 and 1
            weights[i] = r - 0.5;
        }
    }
}
pub fn genann_copy(ann: &Genann) -> Option<Genann> {
    // Create a new Genann instance by cloning the input
    let mut ret = ann.clone();

    // Clone the weight, output, and delta vectors if they exist
    ret.weight = ann.weight.as_ref().map(|weights| weights.clone());
    ret.output = ann.output.as_ref().map(|outputs| outputs.clone());
    ret.delta = ann.delta.as_ref().map(|deltas| deltas.clone());

    Some(ret)
}
pub fn genann_free(ann: Option<Box<Genann>>) {
    // In Rust, the Box will be automatically dropped when it goes out of scope,
    // so no explicit free is needed. The Option wrapper allows for NULL-equivalent behavior.
    // Just let the Box drop naturally by doing nothing.
}

pub fn genann_write(ann: &Genann, out: &mut dyn Write) -> std::io::Result<()> {
    write!(out, "{} {} {} {}", ann.inputs, ann.hidden_layers, ann.hidden, ann.outputs)?;
    
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
    if a > 0.0 { 1.0 } else { 0.0 }
}
pub fn genann_act_linear(ann: &Genann, a: f64) -> f64 {
    a
}
pub fn genann_act_hidden_indirect(ann: &Genann, a: f64) -> f64 {
    (ann.activation_hidden)(ann, a)
}
pub fn genann_act_output_indirect(ann: &Genann, a: f64) -> f64 {
    (ann.activation_output)(ann, a)
}
pub fn helper_genann_train_1(
    j_ref: &mut i32,
    k_ref: &mut i32,
    ann: &mut Genann,
    learning_rate: f64,
    h: i32,
) {
    let mut j = *j_ref;
    let mut k = *k_ref;

    // Get references to the required slices from ann
    let d = ann.delta.as_ref().unwrap();
    let d_start = (h * ann.hidden) as usize;
    let d_slice = &d[d_start..d_start + ann.hidden as usize];

    let i = ann.output.as_ref().unwrap();
    let i_start = if h != 0 {
        (ann.inputs + (ann.hidden * (h - 1))) as usize
    } else {
        0
    };
    let i_slice = &i[i_start..];

    let w = ann.weight.as_mut().unwrap();
    let w_start = if h != 0 {
        ((ann.inputs + 1) * ann.hidden + ((ann.hidden + 1) * ann.hidden) * (h - 1)) as usize
    } else {
        0
    };
    let w_slice = &mut w[w_start..];

    let mut d_idx = 0;
    let mut w_idx = 0;

    for _ in 0..ann.hidden {
        // Update first weight
        w_slice[w_idx] += (d_slice[d_idx] * learning_rate) * -1.0;
        w_idx += 1;

        // Update remaining weights
        let input_count = if h == 0 { ann.inputs } else { ann.hidden };
        for _ in 1..(input_count + 1) {
            w_slice[w_idx] += (d_slice[d_idx] * learning_rate) * i_slice[k as usize - 1];
            w_idx += 1;
            k += 1;
        }

        d_idx += 1;
        j += 1;
    }

    *j_ref = j;
    *k_ref = k;
}
pub fn helper_genann_train_2(
    j_ref: &mut i32,
    k_ref: &mut i32,
    ann: &mut Genann,
    learning_rate: f64,
) {
    // Dereference the mutable references once at the start
    let mut j = *j_ref;
    let mut k = *k_ref;

    // Get references to the Vec<f64> fields, handling the Option
    let d = ann.delta.as_ref().expect("delta is None");
    let d_start = (ann.hidden * ann.hidden_layers) as usize;
    let d_slice = &d[d_start..];
    
    let w = ann.weight.as_mut().expect("weight is None");
    let w_start = if ann.hidden_layers != 0 {
        ((ann.inputs + 1) * ann.hidden) as usize 
            + (((ann.hidden + 1) * ann.hidden) as usize * (ann.hidden_layers - 1) as usize)
    } else {
        0
    };
    let w_slice = &mut w[w_start..];
    let mut w_idx = 0;

    let i = ann.output.as_ref().expect("output is None");
    let i_start = if ann.hidden_layers != 0 {
        (ann.inputs + (ann.hidden * (ann.hidden_layers - 1))) as usize
    } else {
        0
    };
    let i_slice = &i[i_start..];

    for j in 0..ann.outputs {
        w_slice[w_idx] += (d_slice[0] * learning_rate) * -1.0;
        w_idx += 1;

        let limit = if ann.hidden_layers != 0 {
            ann.hidden
        } else {
            ann.inputs
        } + 1;

        for k in 1..limit {
            w_slice[w_idx] += (d_slice[0] * learning_rate) * i_slice[(k - 1) as usize];
            w_idx += 1;
        }

        // Move to next delta value (equivalent to ++d[d_idx] in C)
        let _ = &d_slice[1..];
    }

    debug_assert_eq!(
        (w_idx + w_start) as i32,
        ann.total_weights,
        "Weight index mismatch"
    );

    // Update the reference values
    *j_ref = j;
    *k_ref = k;
}
pub fn helper_genann_train_3(j_ref: &mut i32, k_ref: &mut i32, ann: &mut Genann, h: i32) {
    let mut j = *j_ref;
    let mut k = *k_ref;
    
    // Get references to the vectors safely
    let o = ann.output.as_ref().expect("output not initialized");
    let o_start = (ann.inputs + (h * ann.hidden)) as usize;
    let o_slice = &o[o_start..];
    
    let mut o_idx = 0;
    
    // Get mutable reference to delta
    let d = ann.delta.as_mut().expect("delta not initialized");
    let d_start = (h * ann.hidden) as usize;
    let dd_start = ((h + 1) * ann.hidden) as usize;
    
    // Split the delta vector into two non-overlapping mutable slices
    let (d_slice, rest) = d.split_at_mut(dd_start);
    let d_slice = &mut d_slice[d_start..];
    let dd = &rest[..(dd_start - d_start)];
    
    let mut d_idx = 0;
    
    let ww = ann.weight.as_ref().expect("weight not initialized");
    let ww_start = ((ann.inputs + 1) * ann.hidden + ((ann.hidden + 1) * ann.hidden) * h) as usize;
    let ww_slice = &ww[ww_start..];
    
    for j in 0..ann.hidden {
        let mut delta = 0.0;
        let k_limit = if h == (ann.hidden_layers - 1) {
            ann.outputs
        } else {
            ann.hidden
        };
        
        for k in 0..k_limit {
            let forward_delta = dd[k as usize];
            let windex = (k * (ann.hidden + 1) + (j + 1)) as usize;
            let forward_weight = ww_slice[windex];
            delta += forward_delta * forward_weight;
        }
        
        d_slice[d_idx as usize] = (o_slice[o_idx as usize] * (1.0 - o_slice[o_idx as usize])) * delta;
        d_idx += 1;
        o_idx += 1;
    }
    
    *j_ref = j;
    *k_ref = k;
}

pub fn genann_act_sigmoid_cached(ann: &Genann, a: f64) -> f64 {
    assert!(!a.is_nan(), "Input must not be NaN");
    
    if a < SIGMOID_DOM_MIN {
        return LOOKUP.lock().unwrap()[0];
    }
    if a >= SIGMOID_DOM_MAX {
        return LOOKUP.lock().unwrap()[4095];
    }
    
    let interval = *INTERVAL.lock().unwrap();
    let j = ((a - SIGMOID_DOM_MIN) * interval + 0.5) as usize;
    
    if j >= 4096 {
        return LOOKUP.lock().unwrap()[4095];
    }
    
    LOOKUP.lock().unwrap()[j]
}

pub fn genann_init_sigmoid_lookup(ann: &Genann) {
    let f = (SIGMOID_DOM_MAX - SIGMOID_DOM_MIN) / 4096.0;
    {
        let mut interval_guard = INTERVAL.lock().unwrap();
        *interval_guard = 4096.0 / (SIGMOID_DOM_MAX - SIGMOID_DOM_MIN);
    }

    let mut lookup_guard = LOOKUP.lock().unwrap();
    for i in 0..4096 {
        lookup_guard[i] = genann_act_sigmoid(ann, SIGMOID_DOM_MIN + (f * i as f64));
    }
}

pub fn genann_init(inputs: i32, hidden_layers: i32, hidden: i32, outputs: i32) -> Option<Genann> {
    // Input validation
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

    // Create Genann struct with initialized vectors
    let mut ret = Genann {
        inputs,
        hidden_layers,
        hidden,
        outputs,
        activation_hidden: genann_act_sigmoid_cached,
        activation_output: genann_act_sigmoid_cached,
        total_weights,
        total_neurons,
        weight: Some(vec![0.0; total_weights as usize]),
        output: Some(vec![0.0; total_neurons as usize]),
        delta: Some(vec![0.0; (total_neurons - inputs) as usize]),
    };

    // Initialize weights and sigmoid lookup
    genann_randomize(&mut ret);
    genann_init_sigmoid_lookup(&ret);

    Some(ret)
}

pub fn genann_read(in_stream: &mut dyn Read) -> Option<Genann> {
    let mut buffer = String::new();
    if in_stream.read_to_string(&mut buffer).is_err() {
        eprintln!("Failed to read from input stream");
        return None;
    }

    let mut parts = buffer.split_whitespace();
    let inputs = parts.next().and_then(|s| s.parse().ok())?;
    let hidden_layers = parts.next().and_then(|s| s.parse().ok())?;
    let hidden = parts.next().and_then(|s| s.parse().ok())?;
    let outputs = parts.next().and_then(|s| s.parse().ok())?;

    let mut ann = genann_init(inputs, hidden_layers, hidden, outputs)?;

    if let Some(weight_vec) = &mut ann.weight {
        for i in 0..ann.total_weights as usize {
            if let Some(weight_str) = parts.next() {
                if let Ok(weight) = weight_str.parse() {
                    weight_vec[i] = weight;
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
        eprintln!("No weight vector in Genann");
        return None;
    }

    Some(ann)
}
pub fn genann_run<'a>(ann: &'a mut Genann, inputs: &'a [f64]) -> Option<&'a [f64]> {
    // Check if required fields are present
    let w = ann.weight.as_ref()?;
    
    // Extract all needed fields before any mutable borrow
    let act_hidden = ann.activation_hidden;
    let act_output = ann.activation_output;
    let inputs_count = ann.inputs as usize;
    let hidden_count = ann.hidden as usize;
    let outputs_count = ann.outputs as usize;
    let hidden_layers = ann.hidden_layers;
    let total_weights = ann.total_weights;
    let total_neurons = ann.total_neurons;

    // Create a raw pointer to ann for use in activation functions
    let ann_ptr = ann as *const Genann;
    
    let output = ann.output.as_mut()?;
    
    let mut w_idx = 0;
    let mut o_idx = inputs_count;
    let mut i_idx = 0i32;

    // Copy inputs to the beginning of output buffer
    output[..inputs_count].copy_from_slice(&inputs[..inputs_count]);

    if hidden_layers == 0 {
        let (left, right) = output.split_at_mut(o_idx);
        let mut right = right;
        
        for _ in 0..outputs_count {
            let mut sum = w[w_idx] * -1.0;
            w_idx += 1;
            for k in 0..inputs_count {
                sum += w[w_idx] * left[k + i_idx as usize];
                w_idx += 1;
            }
            let activation = unsafe { act_output(&*ann_ptr, sum) };
            right[0] = activation;
            right = &mut right[1..];
        }
        return Some(&output[o_idx..o_idx + outputs_count]);
    }

    // First hidden layer
    let (left, right) = output.split_at_mut(o_idx);
    let mut right = right;
    for _ in 0..hidden_count {
        let mut sum = w[w_idx] * -1.0;
        w_idx += 1;
        for k in 0..inputs_count {
            sum += w[w_idx] * left[k + i_idx as usize];
            w_idx += 1;
        }
        let activation = unsafe { act_hidden(&*ann_ptr, sum) };
        right[0] = activation;
        right = &mut right[1..];
    }
    o_idx += hidden_count;
    i_idx += inputs_count as i32;

    // Additional hidden layers
    for _ in 1..hidden_layers {
        let (left, right) = output.split_at_mut(o_idx);
        let mut right = right;
        for _ in 0..hidden_count {
            let mut sum = w[w_idx] * -1.0;
            w_idx += 1;
            for k in 0..hidden_count {
                sum += w[w_idx] * left[k + i_idx as usize];
                w_idx += 1;
            }
            let activation = unsafe { act_hidden(&*ann_ptr, sum) };
            right[0] = activation;
            right = &mut right[1..];
        }
        o_idx += hidden_count;
        i_idx += hidden_count as i32;
    }

    let (left, right) = output.split_at_mut(o_idx);
    let mut right = right;
    for _ in 0..outputs_count {
        let mut sum = w[w_idx] * -1.0;
        w_idx += 1;
        for k in 0..hidden_count {
            sum += w[w_idx] * left[k + i_idx as usize];
            w_idx += 1;
        }
        let activation = unsafe { act_output(&*ann_ptr, sum) };
        right[0] = activation;
        right = &mut right[1..];
    }

    assert!((w_idx as i32) == total_weights);
    assert!((o_idx as i32 + outputs_count as i32) == total_neurons);

    Some(&output[o_idx..o_idx + outputs_count])
}
pub fn helper_genann_train_4(j_ref: &mut i32, ann: &mut Genann, desired_outputs: &[f64]) {
    let mut j = *j_ref;
    let activation_output = ann.activation_output;
    let act_output_indirect = genann_act_output_indirect as usize;
    let act_linear = genann_act_linear as usize;
    
    // Extract the values we need before the mutable borrow
    let activation_eq = act_output_indirect == act_linear || activation_output as usize == act_linear;
    let outputs = ann.outputs;
    let inputs = ann.inputs;
    let hidden = ann.hidden;
    let hidden_layers = ann.hidden_layers;

    let o = ann.output.as_ref().unwrap();
    let o_start = (inputs + (hidden * hidden_layers)) as usize;
    let o_slice = &o[o_start..];
    let mut o_idx = 0;

    let d = ann.delta.as_mut().unwrap();
    let d_start = (hidden * hidden_layers) as usize;
    let d_slice = &mut d[d_start..];
    let mut d_idx = 0;

    let t = desired_outputs;
    let mut t_idx = 0;

    if activation_eq {
        for _ in 0..outputs {
            d_slice[d_idx] = t[t_idx] - o_slice[o_idx];
            o_idx += 1;
            t_idx += 1;
            d_idx += 1;
            j += 1;
        }
    } else {
        for _ in 0..outputs {
            let o_val = o_slice[o_idx];
            d_slice[d_idx] = ((t[t_idx] - o_val) * o_val) * (1.0 - o_val);
            d_idx += 1;
            o_idx += 1;
            t_idx += 1;
            j += 1;
        }
    }
    *j_ref = j;
}
pub fn genann_train(ann: &mut Genann, inputs: &[f64], desired_outputs: &[f64], learning_rate: f64) {
    // Run the network first
    genann_run(ann, inputs);
    
    let mut j = 0;
    let mut k = 0;
    
    // First helper call
    {
        helper_genann_train_4(&mut j, ann, desired_outputs);
    }
    
    // Backward pass through hidden layers
    for h in (0..ann.hidden_layers).rev() {
        helper_genann_train_3(&mut j, &mut k, ann, h);
    }
    
    // Update weights for output layer
    {
        helper_genann_train_2(&mut j, &mut k, ann, learning_rate);
    }
    
    // Update weights for hidden layers
    for h in (0..ann.hidden_layers).rev() {
        helper_genann_train_1(&mut j, &mut k, ann, learning_rate, h);
    }
}
