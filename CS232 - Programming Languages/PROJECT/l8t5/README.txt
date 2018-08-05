I didn’t quite understand the depth of task 5 and planned all exams and other assignments for other classes for before task5. I understand the implementation for how task 5 will work, and it would only take me another day or two to implement the task. 

There are 3 types of nodes in which the “root” node of the assignment(let) operation, is a let node at the very top. let’s op1 is a let_list and op2 is where the eval() goes. The let_list’s op1 will be a let_elem node, and let_lists op2 would be another null unless another assignment were to be needed. In which, the tree would grow down that node and start with more letl_ists. Let_elem’s op1 would be a symbol node with the name of the symbol as its data. And Let_elem’s op2 would be the value assigned to that symbol in op1.

To store the variables to their associated values, a symbol table would be used, and lookup would be generally easy.


					Ex: (add (let a 1) (let b 2))

					[let]
					/   \
				[let_list]   [eval()]
			      / 	\	     \
			[let_elem]     [let_list]    [+]
			/    \		/	 \     /\
		     [a]    [1]   [let_elem]	     [a][b]
				      /   \
				    [b]   [2]