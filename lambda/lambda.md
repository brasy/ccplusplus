# lambda 表达式
`[capture_block](parameter) mutable exception_specification -> return_type {body}`
## 捕捉块(capture block)
> 指定如何捕捉所在作用域中的变量，并供给lambda主体部分使用。
 * 参数(parameter):(可选)lambda表达式使用的参数列表。只有在不需要任何参数并且没有指定mutable、一个exception_specification和一个return_type的情况下可以忽略该列表。
 * 参数列表和普通函数的参数列表类似，区别如下:
 * 参数不能有默认值
 * 不允许变长参数列表
 * 不允许未命名的参数
  ###   捕捉方法
> 两种方式来捕捉所在作用域中的所有变量:
 * [=]通过值捕捉所有变量
 * [&]通过引用捕捉所有变量
 * 空白的捕捉块[]表示不从所在作用域中捕捉变量
 *
 * [&x]只通过引用捕捉x，不捕捉其他变量
 * [x]只通过值捕捉x，不捕捉其他变量
 * [=,&x, &y]默认通过值捕捉，变量x和y是例外，这两个变量通过引用捕捉
 * [&, x]默认通过引用捕捉，变量x是例外，这个变量通过值捕捉
 * [&x, &x]非法，因为标识符不允许重复
 * 通过引用捕捉变量的时候，一定要保证当lambda表达式在执行的时候这个引用还是可用的

## mutable
> (可选)如果所在作用域中的变量是通过值捕捉的，那么lambda表达式主体中可以使用这些变量的副本。这些副本默认标记为const，因此lambda表达式主体不能修改这些副本的值。
如果lambda表达式标记为mutable，那么这些副本则不是const，因此主体可以修改这些本地副本。

## exception_specification
> (可选)用于指定lambda表达式可以抛出的异常。
## return_type
> (可选)返回值的类型。如果忽略了return_type，那么编译器会根据以下原则判断返回类型:
 * 如果lambda表达式主体的形式为{ return expression;}，那么lambda表达式的return_type为expression的类型。
 * 其他情况下的return_type为void
 * lambda表达式最后如果加()小括号,则表示立即执行, 类似普通函数func(),这时候的返回值就是函数返回值了
