CREATE VIEW [dbo].[ViewRecords]
AS
SELECT     dbo.Records.ID, dbo.Records.Title, dbo.Records.ArtistID, dbo.Records.[Date], dbo.Records.LabelID, dbo.Records.Producer, dbo.Records.Studio, 
                      dbo.Records.Remarks, dbo.Records.Cover, dbo.Artists.Name AS Artist, dbo.RecordLabel.Name AS Label
FROM         dbo.Records LEFT OUTER JOIN
                      dbo.RecordLabel ON dbo.Records.LabelID = dbo.RecordLabel.ID LEFT OUTER JOIN
                      dbo.Artists ON dbo.Records.ArtistID = dbo.Artists.ID


