
CREATE VIEW [dbo].[ViewBusinessOnTraffic]
AS
SELECT BlockID, BlockDate, TypeOfBusinessID, COUNT(*) 
    AS N
FROM dbo.ViewTraffic
GROUP BY BlockID, BlockDate, TypeOfBusinessID

