; Open ports for the input and output files
(define in-file (open-input-file "input.txt"))
(define out-file (open-output-file "output.txt"))
 
; Read and write tokens from the input file
; to the output file one by one until end of file
(do ((tok (read in-file) (read in-file))) ;;; ( <variable> <init> <step> )
        ((eof-object? tok))               ;;; <test end cond>
        (display tok)                     ;;; <command>
        (write tok out-file)              ;;; <command>
		  (newline out-file))               ;;; <command>
 
; Close the ports
(close-input-port in-file)
(close-output-port out-file)

