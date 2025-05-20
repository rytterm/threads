
.global ctx_restore
.type   ctx_restore,    @function
ctx_restore:
    mov (%rdi),      %rsp
    ret

.global ctx_save
.type   ctx_save,       @function
ctx_save:
    mov %rsp,       (%rdi)
    ret


.global ctx_switch
.type   ctx_switch,     @function
ctx_switch:
    mov %rsp,       (%rdi)
    mov (%rsi),     %rsp
    ret


.section .note.GNU-stack,"",@progbits
