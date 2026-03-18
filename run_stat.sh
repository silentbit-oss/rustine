#!/bin/bash

BUILDS_PATH=$1
COMMANDS=("c2rust" "c2saferrust" "crown" "laertes" "syzygy" "rustmap", "orbit", "recode")
ARTIFACTS=$(ls artifacts);

for dir in $ARTIFACTS; do
    echo "$dir"
    ./scripts/count_c_project_line.sh "subjects/$dir" | jq . > "artifacts/$dir/stat/c_loc_files.json"
    python pipeline stat $BUILDS_PATH/$dir > artifacts/$dir/stat/c_fragments.json || true
done

for COMMAND in "${COMMANDS[@]}"; do
    echo "........... $COMMAND ..........."
    for dir in $ARTIFACTS; do
        echo "Working on $dir"
        if [ -d "artifacts/$dir/others/$COMMAND" ]; then
            echo "RUNNING CLIPPY ..."
            cd "artifacts/$dir/others/$COMMAND"
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -W clippy::all 2>&1 | grep "warning:" | grep -v generated > "../../stat/${COMMAND}_clippy.txt"
            rm -rf target
            rm Cargo.lock

            echo "RUNNING METRICS ..."
            RUSTUP_TOOLCHAIN=nightly-2022-08-08 cargo metrics > "../../stat/${COMMAND}_rust_unsafe_raw_pointer.txt"
            rm -rf target
            rm Cargo.lock

            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo build 2>&1 | grep "warning:" | grep -v generated > build.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::correctness 2>&1 | grep "warning:" | grep -v generated > correctness.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::suspicious 2>&1 | grep "warning:" | grep -v generated > suspicious.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::style 2>&1 | grep "warning:" | grep -v generated > style.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::complexity 2>&1 | grep "warning:" | grep -v generated > complexity.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::perf 2>&1 | grep "warning:" | grep -v generated > perf.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::pedantic 2>&1 | grep "warning:" | grep -v generated > pedantic.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::restriction 2>&1 | grep "warning:" | grep -v generated > restriction.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::nursery 2>&1 | grep "warning:" | grep -v generated > nursery.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::cargo 2>&1 | grep "warning:" | grep -v generated > cargo.txt

            sort -o build.txt build.txt
            sort -o correctness.txt correctness.txt
            sort -o suspicious.txt suspicious.txt
            sort -o style.txt style.txt
            sort -o complexity.txt complexity.txt
            sort -o perf.txt perf.txt
            sort -o pedantic.txt pedantic.txt
            sort -o restriction.txt restriction.txt
            sort -o nursery.txt nursery.txt
            sort -o cargo.txt cargo.txt

            diff build.txt correctness.txt | grep '^>' | sed 's/^> //' > "../../stat/${COMMAND}_correctness_clippy.txt"
            diff build.txt suspicious.txt | grep '^>' | sed 's/^> //' > "../../stat/${COMMAND}_suspicious_clippy.txt"
            diff build.txt style.txt | grep '^>' | sed 's/^> //' > "../../stat/${COMMAND}_style_clippy.txt"
            diff build.txt complexity.txt | grep '^>' | sed 's/^> //' > "../../stat/${COMMAND}_complexity_clippy.txt"
            diff build.txt perf.txt | grep '^>' | sed 's/^> //' > "../../stat/${COMMAND}_perf_clippy.txt"
            diff build.txt pedantic.txt | grep '^>' | sed 's/^> //' > "../../stat/${COMMAND}_pedantic_clippy.txt"
            diff build.txt restriction.txt | grep '^>' | sed 's/^> //' > "../../stat/${COMMAND}_restriction_clippy.txt"
            diff build.txt nursery.txt | grep '^>' | sed 's/^> //' > "../../stat/${COMMAND}_nursery_clippy.txt"
            diff build.txt cargo.txt | grep '^>' | sed 's/^> //' > "../../stat/${COMMAND}_cargo_clippy.txt"
            rm *.txt
            rm -rf target
            rm Cargo.lock
            cd -
        else
            echo " --------------------------> NOT FOUND $COMMAND in $dir"
        fi
    done
done

for dir in $ARTIFACTS; do
    TRANSLATIONS=$(ls artifacts/$dir/ | grep transl)
    for tr in $TRANSLATIONS; do
        echo "Working on $dir ---> $tr"
        if [ -d "artifacts/$dir/$tr" ]; then
            echo "RUNNING CLIPPY ..."
            cd "artifacts/$dir/$tr"
            RUSTUP_TOOLCHAIN=nightly-2025-05-13 cargo clippy --no-deps -- -W clippy::all 2>&1 | grep "warning:" | grep -v generated > "../stat/rustify_${tr}_clippy.txt"
            rm -rf target
            rm Cargo.lock

            echo "RUNNING METRICS ..."
            RUSTUP_TOOLCHAIN=nightly-2025-05-13 cargo newmetrics > "../stat/rustify_${tr}_rust_unsafe_raw_pointer.txt"
            rm -rf target
            rm Cargo.lock

            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo build 2>&1 | grep "warning:" | grep -v generated > build.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::correctness 2>&1 | grep "warning:" | grep -v generated > correctness.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::suspicious 2>&1 | grep "warning:" | grep -v generated > suspicious.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::style 2>&1 | grep "warning:" | grep -v generated > style.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::complexity 2>&1 | grep "warning:" | grep -v generated > complexity.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::perf 2>&1 | grep "warning:" | grep -v generated > perf.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::pedantic 2>&1 | grep "warning:" | grep -v generated > pedantic.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::restriction 2>&1 | grep "warning:" | grep -v generated > restriction.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::nursery 2>&1 | grep "warning:" | grep -v generated > nursery.txt
            RUSTUP_TOOLCHAIN=nightly-2025-05-25 cargo clippy --no-deps -- -A clippy::all -W clippy::cargo 2>&1 | grep "warning:" | grep -v generated > cargo.txt

            sort -o build.txt build.txt
            sort -o correctness.txt correctness.txt
            sort -o suspicious.txt suspicious.txt
            sort -o style.txt style.txt
            sort -o complexity.txt complexity.txt
            sort -o perf.txt perf.txt
            sort -o pedantic.txt pedantic.txt
            sort -o restriction.txt restriction.txt
            sort -o nursery.txt nursery.txt
            sort -o cargo.txt cargo.txt

            diff build.txt correctness.txt | grep '^>' | sed 's/^> //' > "../stat/rustify_${tr}_correctness_clippy.txt"
            diff build.txt suspicious.txt | grep '^>' | sed 's/^> //' > "../stat/rustify_${tr}_suspicious_clippy.txt"
            diff build.txt style.txt | grep '^>' | sed 's/^> //' > "../stat/rustify_${tr}_style_clippy.txt"
            diff build.txt complexity.txt | grep '^>' | sed 's/^> //' > "../stat/rustify_${tr}_complexity_clippy.txt"
            diff build.txt perf.txt | grep '^>' | sed 's/^> //' > "../stat/rustify_${tr}_perf_clippy.txt"
            diff build.txt pedantic.txt | grep '^>' | sed 's/^> //' > "../stat/rustify_${tr}_pedantic_clippy.txt"
            diff build.txt restriction.txt | grep '^>' | sed 's/^> //' > "../stat/rustify_${tr}_restriction_clippy.txt"
            diff build.txt nursery.txt | grep '^>' | sed 's/^> //' > "../stat/rustify_${tr}_nursery_clippy.txt"
            diff build.txt cargo.txt | grep '^>' | sed 's/^> //' > "../stat/rustify_${tr}_cargo_clippy.txt"
            rm *.txt
            rm -rf target
            rm Cargo.lock
            cd -
        else
            echo " --------------------------> NOT FOUND $dir $tr"
        fi
    done
done

for dir in $ARTIFACTS; do
    TRANSLATIONS=$(ls artifacts/$dir/ | grep transl)
    for tr in $TRANSLATIONS; do
        if [ -d "artifacts/$dir/$tr" ]; then
            echo "RUSTIFY : $dir"
            python legacy/Tools/readability_rust.py "artifacts/$dir/$tr" > "artifacts/$dir/stat/rustify_${tr}_code_metrics.json"
            ./scripts/rust_code_quality.sh "artifacts/$dir/$tr" > "artifacts/$dir/stat/rustify_${tr}_code_quality.json"
            ./scripts/count_rust_project_line.sh "artifacts/$dir/$tr/src" > "artifacts/$dir/stat/rustify_${tr}_loc_files.json"
            grep -orE '\.add\(|\.sub\(|\.offset\(|\.offset_from\(|\.byte_add\(|\.byte_sub\(|\.byte_offset\(|\.wrapping_add\(|\.wrapping_sub\(|\.wrapping_offset\(|\.wrapping_byte_add\(|\.wrapping_byte_sub\(' "artifacts/$dir/$tr" > "artifacts/$dir/stat/rustify_${tr}_rust_pointer_arithmetic.txt"
        fi
    done

    for COMMAND in "${COMMANDS[@]}"; do
        if [ -d "artifacts/$dir/others/$COMMAND" ]; then
            echo "........... $dir - $COMMAND ..........."
            python legacy/Tools/readability_rust.py "artifacts/$dir/others/$COMMAND" > "artifacts/$dir/stat/${COMMAND}_code_metrics.json"
            ./scripts/rust_code_quality.sh "artifacts/$dir/others/$COMMAND" > "artifacts/$dir/stat/${COMMAND}_code_quality.json"
            ./scripts/count_rust_project_line.sh "artifacts/$dir/others/$COMMAND" > "artifacts/$dir/stat/${COMMAND}_loc_files.json"
        fi
    done
done

find artifacts -name "*clippy*" -exec bash -c 'echo -e "{}: \n$(cat "{}" | sort | uniq -c | sort -r)\n\n"' \; > clippy_categories.txt
find artifacts -name "*clippy*" -exec bash -c 'echo "{}: $(wc -l < "{}") lines"' \; > clippy_warnings_count.txt
find artifacts -name "*rust_pointer_arithmetic.txt" -exec bash -c 'echo "{}: $(wc -l < "{}") lines"' \; > rust_pointer_arithmetic_count.txt

find artifacts -name decls.txt | xargs rm
find artifacts -name derefs.txt | xargs rm
find artifacts -name unsafe_spans.txt | xargs rm

grep -r "Unsafe lines" artifacts/*/stat/ > unsafe_lines.txt
grep -r "Unsafe calls" artifacts/*/stat/ > unsafe_calls.txt
grep -r "Unsafe casts" artifacts/*/stat/ > unsafe_casts.txt
grep -r "Raw pointer dereferences" artifacts/*/stat/ > raw_pointer_deref.txt
grep -r "Raw pointer declarations" artifacts/*/stat/ > raw_pointer_decl.txt
