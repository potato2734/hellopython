# tuple
a=(1,2) # 소괄호로 튜플 출력
print(a)
a=(1,2,) # 콤마 남겨도 출력
print(a)
b=(1)
print(b) # 원소 1개는 튜플로 취급안함
b=(1,)
print(b) # 추후에 비교할게 있다고 판별하고 튜플로 인정
c=('apple',True,2.5)
print(c)
c=('apple',a,b)
print(c) # 튜플도 포함시킬 수 있음 / 말그대로 부분집합
for i in range(-3,3): # 튜플의 범위는 위로 초과는 못하고 아래로 하향은 1사이클 가능함(왼쪽과 같은 상황이 가능한 모든 범위 출력한 상태)
    print(c[i])
print(c[-1:])

d=(a,'hello',False)
print(True in d)
print('hello' in d)
print(a in d)
print(a+d) # 튜플끼리 합칠 수 있음
print(a*3) # 튜플 연달아 3번 출력
# print(a*b) 튜플끼리의 곱은 불가능
print(a.index(2)) # a튜플 몇번째에 2가 있는지 출력
e=(1,2,2,3,3,3)
print(e.count(2),e.count(3)) # 해당 원소가 튜플에 몇개나 존재하는지 출력
x=tuple(('hi',23)) # 소괄호 2번 쳐야 됨
print(x)
print('\n')



# list
a=[] # 대괄호로 리스트 생성
a=[1,2,3]
print(a) # 대괄호 포함해서 출력
b=[1,2,3,]
print(b) # 마지막에 콤마 찍혀 있어도 그냥 출력
a=[1]
print(a)
c=list([1,2,3,4]) # 대괄호 포함해서 튜플화
print(c)
# 범위 이용해 출력, 개수 새는 방식은 튜플과 일치
c.append(100)
print(c) # 추가
c.extend([3,[12,23]]) # 리스트 형태로 입력한 원소들을 추가
print(c)
c.insert(3,"hello") # (3+1)번째 자리에 'hello'추가 .문자를 넣고 싶으면 쌍따옴표!!! -> 작은 따옴표로 출력
print(c)
c.remove(1) # 삭제
print(c)
for i in range (1,3): # 앞에거부터 1개씩 삭제
    c.remove(3)
    print(c)
d=c.pop(0) # 리스트c에서 몇번째 원소를 튀어나오게 할 것인지 d에 저장
print(d)
c.clear() # 리스트 비우기
print(c)
z=[1,2,3,4,'hello']
print(z.index("hello")) # 해당 원소가 몇번째에 있는지 확인
z.extend([3,1,4,1,5]) # 마지막에 추가
print(z)
print(z.count(3)) # 3이 몇개나 있는지 출력
# z.sort()
# print(z) # 중간에 다른 자료형('hello')이 껴 있어 출력 안됨
z.remove('hello') # 지울 때는 쌍따옴표가 아닌 원소 그 자체
print(z)
z.sort() # 오름차순으로 정렬
print(z)
z.sort(reverse=True) # 내림차순으로 정렬
print(z)
print(list(reversed(z))) # 그냥 순서만 반대로 전환
print(z[::-1]) # 반대로의 다른 표기
print(z.copy())
a='1,2,3,4,5'
p=a.split(',') # 콤마를 기준으로 나누기
print(p)
a='1 2  3  4  5'
p=a.split('  ') # 공백 2칸을 기준으로 나누기
print(p)
a='hello world !'
t1,t2,t3=a.split(' ')
print(t1)
print(t2)
print(t3)
