FROM gcc:12
WORKDIR /app
COPY . .
RUN g++ -std=c++17 -O2 -pthread -o ej01_async_future ej01_async_future.cpp && \
    g++ -std=c++17 -O2 -pthread -o ej02_promise_future ej02_promise_future.cpp && \
    g++ -std=c++17 -O2 -pthread -o ej03_packaged_task ej03_packaged_task.cpp && \
    g++ -std=c++17 -O2 -pthread -o ej04_thread_pool ej04_thread_pool.cpp && \
    g++ -std=c++20 -O2 -pthread -o ej05_coroutines_cpp20 ej05_coroutines_cpp20.cpp
CMD ./ej01_async_future && echo "" && echo "---" && echo "" && \
    ./ej02_promise_future && echo "" && echo "---" && echo "" && \
    ./ej03_packaged_task && echo "" && echo "---" && echo "" && \
    ./ej04_thread_pool && echo "" && echo "---" && echo "" && \
    ./ej05_coroutines_cpp20
