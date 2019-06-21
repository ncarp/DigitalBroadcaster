
CREATE VIEW [dbo].[ViewEditedMusicFiles]
AS
SELECT RTRIM(dbo.HD.Path) + '\' + RTRIM(dbo.Artists.Name) 
    + ' - ' + RTRIM(dbo.MusicTracks.Title) 
    + RTRIM(dbo.MusicTracks.FileType) AS FileName, 
    dbo.MusicTracks.Activ, dbo.MusicTracks.ID AS TrackID
FROM dbo.MusicTracks INNER JOIN
    dbo.Artists ON 
    dbo.MusicTracks.ArtistID = dbo.Artists.ID INNER JOIN
    dbo.HD ON dbo.MusicTracks.PathID = dbo.HD.ID



