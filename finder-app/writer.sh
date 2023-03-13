writefile=$1
writestr=$2

mkdir -p $writefile
rm -r $writefile
touch $writefile

echo $writestr > $writefile