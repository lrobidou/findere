
pdf(file="fpr_size_wikipedia.pdf",width=6,height=4)
resetPar <- function() {
  dev.new()
  op <- par(no.readonly = TRUE)
  dev.off()
  op
}
resetPar()


dev.new()



#par(mar=c(5,5,3,6), cex.axis=2, cex.lab=2, cex.main = 2)
# par(mar=c(5,5,3,6))
data = read.table("data_findereOnWikipedia.txt", head=T)
data$sizeGiga = data$size/8000000000
100/8000000000

dev.off()
plot(data$FPR_findere~data$sizeGiga,xlab="Bloom Filter size (GB)",ylab="FP rate (%) - log scale",pch=15, 
     col="red", log="y",
     yaxt="n",xaxt="n",
     bg = "red", type="l",  cex=2, main="False positive rate, wikipedia corpus, \
     depending on the Bloom filter size, K=31, z=3", 
     cex.main = 1, cex.lab = 1, cex.axis = 1,
     ylim=c(0.01, 100), xlim=c(0, 15))
points(data$FPR_BF~data$sizeGiga,type="l",xlab="",ylab="",pch=19, lty=2, col="blue",  cex=1)

yticks<-c(0.01,0.1,0.5,1,5,10, 50)
axis(2,at=yticks,labels=yticks)
xticks<-c(100/8000000000,2,4,6,8,10,12,14,16)
axis(1,at=xticks,labels=xticks)



par(new = TRUE)#, mar=c(5,5,3,6))

legend( x="top", 
        legend=c("Bloom filter","findere"), 
        col=c("blue","red"), lty=c(2,1),
        lwd=1, merge=TRUE, bty = "n", cex=c(1,1) )


dev.off()



