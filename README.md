# Secure-Boot-Signature
Retrieve secure boot sign 

# Secure Boot State Checker and Variable Manipulator

This UEFI application, developed using the UEFI framework, serves as a tool to check the Secure Boot state and EFI variables. With a concise and efficient codebase, it provides valuable insights into the system's security posture and allows check to the SecureBoot variable.

## Introduction 

This UEFI application analyzes the Secure Boot state by retrieving the SecureBoot variable. It distinguishes between secure and non-secure boot modes, aiding in system diagnostics. Additionally, the application demonstrates the manipulation of EFI variables [not SecureBoot variable  #readonly]. Developers can leverage this code for security-related customizations, ensuring optimal system configurations. Ideal for UEFI-compatible systems, this tool contributes to secure boot management.

## Features

- **Secure Boot State Check:** Determines if the platform firmware operates in secure boot mode.
  
- **EFI Variable Manipulation:** Illustrates how to retrieve and modify EFI variables, focusing on the SecureBoot variable.

## Usage

1. **Build:** Compile the application using UEFI-compatible development tools.

2. **Load:** Load the compiled application onto a UEFI-compatible system.

3. **Run:** Execute the application to check and manipulate the Secure Boot state.

## Code Overview

The code employs UEFI protocols and libraries, showcasing efficient methods for handling EFI variables. Key sections include Secure Boot state retrieval, EFI variable allocation, and modification. Developers can adapt and extend this code for broader security-related applications.

## License

This project is licensed under the [MIT License](LICENSE).

Feel free to modify and utilize the code, and contributions are welcome!

## Acknowledgments

Special thanks to the UEFI community and contributors.

---

*Note: Ensure compatibility with UEFI firmware-based systems before use.*

