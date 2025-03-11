#!/bin/bash

SCRIPT_DIR="$(cd -- "$(dirname "$0")" >/dev/null 2>&1 && pwd -P)"
cd $SCRIPT_DIR

breakpoint() {
  echo -e "\n(Breakpoint... ⏳)"
  read -r
}

continue_demo() {
  echo -e "\n(Next... ⏳)"
  read -r
  clear
}

print_box() {
    local message="$1"
    local length=${#message}
    local padding=4  # Space for the borders and extra padding
    local width=$((length + padding + $2))
    local border=$(printf '═%.0s' $(seq 1 $width))

    echo -e "\033[1;36m╔$border╗"
    printf "║ %s ║\n" "$message"
    echo -e "╚$border╝\033[0m"
}

print_subsection() {
    local message="$1"

    printf "\n\033[1;33m║ %s ║\033[0m\n" "$message"
}


run_command() {
    echo -e "\n\033[1;32m💻 Running: $1\033[0m"
    eval "$1"
}

print_hr() {
    local length="${1:-75}"

    printf "\n\033[1;34m%s\033[0m\n" "$(printf '─%.0s' $(seq 1 "$length"))"
}


clear # Clear the screen for a clear start

echo -e "\033[1;32m"
echo "  C509" | toilet -f ascii12
echo -e "\033[0m"

print_box "🚀 Welcome to the Post-Quantum Natively-Signed C509 Certificates Demo! 🌍🔐" 1

echo -e "\n📢 This demo will guide you through a journey into the future of cryptographic certificates!"
echo -e "🔎 I will be showcasing the magic of natively-signed C509 certificates with post-quantum step by step."
echo -e "\n🥖 Now, let's bake this demo! 🍞"

continue_demo

echo -e "✅ The oven is heating up! Stay tuned for the next step..."

mkdir -p build
run_command "cmake -DENABLE_GEN_ZCBOR_CODEC=ON -B ./build"
cd build
cmake ..
make
cd ..

# Setup
cd $SCRIPT_DIR/build/src/cli
rm -rf ./ca
mkdir -p ./ca
rm -rf ./client
mkdir -p ./client

echo -e "\n🔢 Some libraries (like ZCBOR) offer (limited) support for parser generation based on CDDL schemas."

breakpoint

cat $SCRIPT_DIR/resource/c509.cddl.raw

echo -e "\n\n⚙️ Before going further, look into the ./build/gen for the ZCBOR generated codecs for C509."

continue_demo

# Inform the viewer about the CLI interaction
print_box "📢 This tool has a CLI interface! 🛠️" 0

echo -e "\n🚀 During this demo, each command will be \033[1;32mdisplayed in green\033[0m before being executed."
echo -e "📜 This allows you to follow along and see exactly what's happening under the hood.\n"

continue_demo

print_box "📜 Certification Authority (CA)" -1
print_subsection "🔐 Public Key Generation - CBOR Encoded"
print_hr

breakpoint

run_command "./c509_cli genpkey"

breakpoint

run_command "./c509_cli genpkey -algorithm mldsa87 -out ./ca/ca_key.bin"
run_command "ls -l ./ca"
continue_demo

print_box "📜 Certification Authority (CA)" -1
print_subsection "🪪 Self-Signed Certificate"
print_hr

breakpoint

run_command "./c509_cli req"

breakpoint

run_command "./c509_cli req -new -c509 -set_serial 1 -days 7300 -key ./ca/ca_key.bin -out ./ca/ca_cert.bin"
run_command "ls -l ./ca"

echo -e "\n🧐 Let's look at the CA files in more detail - going to cbor.me."

continue_demo

print_box "📜 Client" -1
print_subsection "🔐 Request a CA-Signed Certificate - CBOR Encoded"
print_hr

breakpoint

run_command "./c509_cli genpkey -algorithm mldsa87_ed448 -out ./client/client_key.bin"

breakpoint

run_command "./c509_cli req -new -subj \"/C=RO/ST=Timis/L=Timisoara/O=UPT/OU=CS/CN=upt.ro/emailAddress=alin.rosu@upt.ro\" -addext \"subjectKeyIdentifier=critical, someKeyIdentifier\" -key ./client/client_key.bin -out ./client/client_csr.bin"

breakpoint

run_command "./c509_cli req -c509 -set_serial 2 -in ./client/client_csr.bin -verify -CA ./ca/ca_cert.bin -CAkey ./ca/ca_key.bin -out ./client/client_cert.bin"
run_command "./c509_cli req -c509 -set_serial 2 -in ./client/client_csr.bin -verify -CA ./ca/ca_cert.bin -CAkey ./ca/ca_key.bin -compressed -out ./client/client_cert_compressed.bin"

run_command "ls -l ./client"

echo -e "\n🔍 Let's look at the client files in more detail - going to cbor.me."

continue_demo

print_box "☑️ We also have tests" -2
print_hr

cd $SCRIPT_DIR/build/test/

breakpoint

run_command "./c509_tests"

echo -e "\n🚀 Tests were really executed. They mostly focus on correct encoding and decoding of frequently used structures."

continue_demo

echo -e ""
echo "✨✨ THANK YOU FOR YOUR ATTENTION! ✨✨" | toilet -f wideterm -F border | lolcat
echo -e "\033[0m"
printf "              \033[1;32m║ %s ║\033[0m\n" "🎉 Hope you enjoyed the demo! 🙌"
echo "   Questions? " | toilet -f smmono9 -F metal
echo -e "                       Alin-Petru \e[31mRosu\e[0m"
echo -e "                  rosualinpetru@gmail.com"

echo -e "\n                 \033[90m(Exiting in 15 seconds...)\033[0m"
sleep 15

clear
