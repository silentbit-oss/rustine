extern crate proc_macro;

use proc_macro::TokenStream;
use quote::quote;
use syn::{parse_macro_input, ItemFn};

#[proc_macro_attribute]
pub fn trace(_attr: TokenStream, item: TokenStream) -> TokenStream {
    let input = parse_macro_input!(item as ItemFn);
    let sig = &input.sig;
    let block = &input.block;
    let vis = &input.vis;
    let attrs = &input.attrs;
    let name_str = sig.ident.to_string();

    let result = quote! {
        #(#attrs)*
        #vis #sig {
            let _log_guard = trace_utils::LogGuard::new(#name_str);
            #block
        }
    };
    result.into()
}
