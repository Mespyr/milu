#include "../include/compiler.h"

void compile_to_asm(std::map<std::string, std::vector<Op>> program, std::string output_filename)
{
    File outfile(output_filename, MODE_WRITE);

    // write boilerplate into file
    outfile.writeln("section .text");
    outfile.writeln("global _start");
    outfile.writeln("dump:");
    outfile.writeln("\tmov r9, -3689348814741910323");
    outfile.writeln("\tsub rsp, 40");
    outfile.writeln("\tmov BYTE [rsp+31], 10");
    outfile.writeln("\tlea rcx, [rsp+30]");
    outfile.writeln(".L2:");
    outfile.writeln("\tmov rax, rdi");
    outfile.writeln("\tlea r8, [rsp+32]");
    outfile.writeln("\tmul r9");
    outfile.writeln("\tmov rax, rdi");
    outfile.writeln("\tsub r8, rcx");
    outfile.writeln("\tshr rdx, 3");
    outfile.writeln("\tlea rsi, [rdx+rdx*4]");
    outfile.writeln("\tadd rsi, rsi");
    outfile.writeln("\tsub rax, rsi");
    outfile.writeln("\tadd eax, 48");
    outfile.writeln("\tmov BYTE [rcx], al");
    outfile.writeln("\tmov rax, rdi");
    outfile.writeln("\tmov rdi, rdx");
    outfile.writeln("\tmov rdx, rcx");
    outfile.writeln("\tsub rcx, 1");
    outfile.writeln("\tcmp rax, 9");
    outfile.writeln("\tja .L2");
    outfile.writeln("\tlea rax, [rsp+32]");
    outfile.writeln("\tmov edi, 1");
    outfile.writeln("\tsub rdx, rax");
    outfile.writeln("\txor eax, eax");
    outfile.writeln("\tlea rsi, [rsp+32+rdx]");
    outfile.writeln("\tmov rdx, r8");
    outfile.writeln("\tmov rax, 1");
    outfile.writeln("\tsyscall");
    outfile.writeln("\tadd rsp, 40");
    outfile.writeln("\tret");
    
    std::vector<std::string> strings;
    
    for (auto fn_key = program.begin(); fn_key != program.end(); fn_key++)
    {
        std::vector<Op> function = fn_key->second;
        std::string func_name = fn_key->first;

        if (func_name == "main")
        {
            outfile.writeln("_start:");
            outfile.writeln("\tmov [args_ptr], rsp");
            outfile.writeln("\tmov rax, ret_stack_end");
            outfile.writeln("\tmov [ret_stack_rsp], rax");
        }
        else
        {
            outfile.writeln(fn_key->first + ":");
            outfile.writeln("\tmov [ret_stack_rsp], rsp");
            outfile.writeln("\tmov rsp, rax");
        }

        for (int ip = 0; ip < function.size(); ip++)
        {
            Op op = function.at(ip);
            
            // debugging
            if (op.type == OP_DUMP)
            {
                outfile.writeln("\t; OP_DUMP");
                outfile.writeln("\tpop rdi");
                outfile.writeln("\tcall dump");
            }
            
            // arithmetics
            else if (op.type == OP_PLUS)
            {
                outfile.writeln("\t; OP_PLUS");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tadd rbx, rax");
                outfile.writeln("\tpush rbx");
            } 
            else if (op.type == OP_MINUS)
            {
                outfile.writeln("\t; OP_MINUS");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tsub rbx, rax");
                outfile.writeln("\tpush rbx");
            }
            else if (op.type == OP_MUL)
            {
                outfile.writeln("\t; OP_MUL");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tmul rbx");
                outfile.writeln("\tpush rax");
            }
            else if (op.type == OP_DIV)
            {
                outfile.writeln("\t; OP_DIV");
                outfile.writeln("\txor rdx, rdx");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tdiv rbx");
                outfile.writeln("\tpush rax");
                outfile.writeln("\tpush rdx");
            }
            
            // comparisons
            else if (op.type == OP_EQUAL)
            {
                outfile.writeln("\t; OP_EQUAL");
                outfile.writeln("\tmov rcx, 0");
                outfile.writeln("\tmov rdx, 1");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tcmp rax, rbx");
                outfile.writeln("\tcmove rcx, rdx");
                outfile.writeln("\tpush rcx");
            }
            else if (op.type == OP_GREATER)
            {
                outfile.writeln("\t; OP_GREATER");
                outfile.writeln("\tmov rcx, 0");
                outfile.writeln("\tmov rdx, 1");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tcmp rax, rbx");
                outfile.writeln("\tcmovg rcx, rdx");
                outfile.writeln("\tpush rcx");
            }
            else if (op.type == OP_LESS)
            {
                outfile.writeln("\t; OP_LESS");
                outfile.writeln("\tmov rcx, 0");
                outfile.writeln("\tmov rdx, 1");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tcmp rax, rbx");
                outfile.writeln("\tcmovl rcx, rdx");
                outfile.writeln("\tpush rcx");
            }
            else if (op.type == OP_GREATER_EQ)
            {
                outfile.writeln("\t; OP_GREATER_EQ");
                outfile.writeln("\tmov rcx, 0");
                outfile.writeln("\tmov rdx, 1");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tcmp rax, rbx");
                outfile.writeln("\tcmovge rcx, rdx");
                outfile.writeln("\tpush rcx");
            }
            else if (op.type == OP_LESS_EQ)
            {
                outfile.writeln("\t; OP_LESS_EQ");
                outfile.writeln("\tmov rcx, 0");
                outfile.writeln("\tmov rdx, 1");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tcmp rax, rbx");
                outfile.writeln("\tcmovle rcx, rdx");
                outfile.writeln("\tpush rcx");
            }
            else if (op.type == OP_NOT_EQ)
            {
                outfile.writeln("\t; OP_NOT_EQ");
                outfile.writeln("\tmov rcx, 0");
                outfile.writeln("\tmov rdx, 1");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tcmp rax, rbx");
                outfile.writeln("\tcmovne rcx, rdx");
                outfile.writeln("\tpush rcx");
            }
            else if (op.type == OP_NOT)
            {
                outfile.writeln("\t; OP_NOT");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tnot rax");
                outfile.writeln("\tpush rax");
            }
            else if (op.type == OP_AND)
            {
                outfile.writeln("\t; OP_AND");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tand rbx, rax");
                outfile.writeln("\tpush rbx");
            }
            else if (op.type == OP_OR)
            {
                outfile.writeln("\t; OP_OR");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tor rbx, rax");
                outfile.writeln("\tpush rbx");
            }
            
            // stack manipulation
            else if (op.type == OP_POP)
            {
                outfile.writeln("\t; OP_POP");
                outfile.writeln("\tpop rax");
            }
            else if (op.type == OP_DUP)
            {
                outfile.writeln("\t; OP_DUP");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpush rax");
                outfile.writeln("\tpush rax");
            }
            else if (op.type == OP_SWP)
            {
                outfile.writeln("\t; OP_SWP");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tpush rax");
                outfile.writeln("\tpush rbx");
            }
            else if (op.type == OP_ROT)
            {
                outfile.writeln("\t; OP_ROT");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tpop rcx");
                outfile.writeln("\tpush rbx");
                outfile.writeln("\tpush rax");
                outfile.writeln("\tpush rcx");
            }
            else if (op.type == OP_OVER)
            {
                outfile.writeln("\t; OP_OVER");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tpush rbx");
                outfile.writeln("\tpush rax");
                outfile.writeln("\tpush rbx");
            }
            
            // memory
            else if (op.type == OP_MEM)
            {
                outfile.writeln("\t; OP_MEM");
                outfile.writeln("\tpush mem");
            }
            else if (op.type == OP_READ8)
            {
                outfile.writeln("\t; OP_READ8");
                outfile.writeln("\tpop rax");
                outfile.writeln("\txor rbx, rbx");
                outfile.writeln("\tmov bl, [rax]");
                outfile.writeln("\tpush rbx");
            }
            else if (op.type == OP_WRITE8)
            {
                outfile.writeln("\t; OP_WRITE8");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tmov [rax], bl");
            }
            else if (op.type == OP_READ16)
            {
                outfile.writeln("\t; OP_READ16");
                outfile.writeln("\tpop rax");
                outfile.writeln("\txor rbx, rbx");
                outfile.writeln("\tmov bx, [rax]");
                outfile.writeln("\tpush rbx");
            }
            else if (op.type == OP_WRITE16)
            {
                outfile.writeln("\t; OP_WRITE16");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tmov [rax], bx");
            }
            else if (op.type == OP_READ32)
            {
                outfile.writeln("\t; OP_READ32");
                outfile.writeln("\tpop rax");
                outfile.writeln("\txor rbx, rbx");
                outfile.writeln("\tmov ebx, [rax]");
                outfile.writeln("\tpush rbx");
            }
            else if (op.type == OP_WRITE32)
            {
                outfile.writeln("\t; OP_WRITE32");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tmov [rax], ebx");
            }
            else if (op.type == OP_READ64)
            {
                outfile.writeln("\t; OP_READ64");
                outfile.writeln("\tpop rax");
                outfile.writeln("\txor rbx, rbx");
                outfile.writeln("\tmov rbx, [rax]");
                outfile.writeln("\tpush rbx");
            }
            else if (op.type == OP_WRITE64)
            {
                outfile.writeln("\t; OP_WRITE64");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tmov [rax], rbx");
            }

            // argv
            else if (op.type == OP_ARGV)
            {
                outfile.writeln("\t; OP_ARGV");
                outfile.writeln("\tmov rax, [args_ptr]");
                outfile.writeln("\tadd rax, 8");
                outfile.writeln("\tpush rax");
            }
            else if (op.type == OP_ARGC)
            {
                outfile.writeln("\t; OP_ARGC");
                outfile.writeln("\tmov rax, [args_ptr]");
                outfile.writeln("\tmov rax, [rax]");
                outfile.writeln("\tpush rax");
            }

            // bitwise
            else if (op.type == OP_SHIFT_LEFT)
            {
                outfile.writeln("\t; OP_SHIFT_LEFT");
                outfile.writeln("\tpop rcx");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tshl rbx, cl");
                outfile.writeln("\tpush rbx");
            }
            else if (op.type == OP_SHIFT_RIGHT)
            {
                outfile.writeln("\t; OP_SHIFT_RIGHT");
                outfile.writeln("\tpop rcx");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tshr rbx, cl");
                outfile.writeln("\tpush rbx");
            }
            else if (op.type == OP_ORB)
            {
                outfile.writeln("\t; OP_ORB");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tor rbx, rax");
                outfile.writeln("\tpush rbx");
            }
            else if (op.type == OP_ANDB)
            {
                outfile.writeln("\t; OP_ANDB");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop rbx");
                outfile.writeln("\tand rbx, rax");
                outfile.writeln("\tpush rbx");
            }
            
            // syscalls
            else if (op.type == OP_SYSCALL1)
            {
                outfile.writeln("\t; OP_SYSCALL1");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop rdi");
                outfile.writeln("\tsyscall");
            }
            else if (op.type == OP_SYSCALL2)
            {
                outfile.writeln("\t; OP_SYSCALL2");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop rsi");
                outfile.writeln("\tpop rdi");
                outfile.writeln("\tsyscall");
            }
            else if (op.type == OP_SYSCALL3)
            {
                outfile.writeln("\t; OP_SYSCALL3");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop rdx");
                outfile.writeln("\tpop rsi");
                outfile.writeln("\tpop rdi");
                outfile.writeln("\tsyscall");
            }
            else if (op.type == OP_SYSCALL4)
            {
                outfile.writeln("\t; OP_SYSCALL4");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop r10");
                outfile.writeln("\tpop rdx");
                outfile.writeln("\tpop rsi");
                outfile.writeln("\tpop rdi");
                outfile.writeln("\tsyscall");
            }
            else if (op.type == OP_SYSCALL5)
            {
                outfile.writeln("\t; OP_SYSCALL5");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop r8");
                outfile.writeln("\tpop r10");
                outfile.writeln("\tpop rdx");
                outfile.writeln("\tpop rsi");
                outfile.writeln("\tpop rdi");
                outfile.writeln("\tsyscall");
            }
            else if (op.type == OP_SYSCALL6)
            {
                outfile.writeln("\t; OP_SYSCALL6");
                outfile.writeln("\tpop rax");
                outfile.writeln("\tpop r9");
                outfile.writeln("\tpop r8");
                outfile.writeln("\tpop r10");
                outfile.writeln("\tpop rdx");
                outfile.writeln("\tpop rsi");
                outfile.writeln("\tpop rdi");
                outfile.writeln("\tsyscall");
            }

            // keywords
            else if (op.type == OP_WHILE)
            {
                outfile.writeln("\t; OP_WHILE");
                outfile.writeln("addr_" + func_name + "_" + std::to_string(ip) + ":");
            }
            else if (op.type == OP_DO)
            {
                outfile.writeln("\t; OP_DO");
                outfile.writeln("\tpop rax");
                outfile.writeln("\ttest rax, rax");
                outfile.writeln("\tjz addr_" + func_name + "_" + std::to_string(op.reference_ip));
            }
            else if (op.type == OP_IF)
            {
                outfile.writeln("\t; OP_IF");
                outfile.writeln("\tpop rax");
                outfile.writeln("\ttest rax, rax");
                outfile.writeln("\tjz addr_" + func_name + "_" + std::to_string(op.reference_ip));
            }
            else if (op.type == OP_ELSE)
            {
                outfile.writeln("\t; OP_ELSE");
                outfile.writeln("\tjmp addr_" + func_name + "_" + std::to_string(op.reference_ip));
                outfile.writeln("addr_" + func_name + "_" + std::to_string(ip) + ":");
            }
            else if (op.type == OP_END)
            {
                outfile.writeln("\t; OP_END");
                if (op.reference_ip != -1)
                    outfile.writeln("\tjmp addr_" + func_name + "_" + std::to_string(op.reference_ip));
                outfile.writeln("addr_" + func_name + "_" + std::to_string(ip) + ":");
            }

            // other 
            else if (op.type == OP_PUSH_INT)
            {
                outfile.writeln("\t; OP_PUSH_INT");
                outfile.writeln("\tmov rax, " + std::to_string(op.push_int));
                outfile.writeln("\tpush rax");
            }
            else if (op.type == OP_PUSH_STR)
            {
                std::string pstr = add_escapes_to_string(op.push_str.substr(1, op.push_str.length() - 1));
                strings.push_back(pstr);
                outfile.writeln("\t; OP_PUSH_STR");
                outfile.writeln("\tmov rax, " + std::to_string(pstr.length()));
                outfile.writeln("\tpush rax");
                outfile.writeln("\tpush str_" + std::to_string(strings.size()));
            }
            else if (op.type == OP_FUNCTION_CALL)
            {
                outfile.writeln("\t; OP_FUNCTION_CALL");
                outfile.writeln("\tmov rax, rsp");
                outfile.writeln("\tmov rsp, [ret_stack_rsp]");
                outfile.writeln("\tcall " + op.push_str);
                outfile.writeln("\tmov [ret_stack_rsp], rsp");
                outfile.writeln("\tmov rsp, rax");
            }
        }
        if (func_name == "main")
        {
            // exit syscall at end of main function
            outfile.writeln("\t; exit");
            outfile.writeln("\tmov rax, 60");
            outfile.writeln("\tmov rdi, 0");
            outfile.writeln("\tsyscall");
        }
        else
        {
            outfile.writeln("\t; return");
            outfile.writeln("\tmov rax, rsp");
            outfile.writeln("\tmov rsp, [ret_stack_rsp]");
            outfile.writeln("\tret");
        }
    }
    

    // data section
    outfile.writeln("section .data");
    for (int i = 0; i < strings.size(); i++)
    {
        std::stringstream ss;

        for (char c : strings.at(i))
            ss << "0x" << std::hex << (int) c << ",";

        outfile.writeln("str_" + std::to_string(i+1) + ": db " + ss.str());
    }

    // bss section
    outfile.writeln("section .bss");
    outfile.writeln("args_ptr: resq 1");
    outfile.writeln("ret_stack_rsp: resq 1");
    outfile.writeln("ret_stack: resb 4096");
    outfile.writeln("ret_stack_end:");
    outfile.writeln("mem: resb 640000");
}
